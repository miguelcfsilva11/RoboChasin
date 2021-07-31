#include "game.h"

using namespace std;

Game::Game(const string &filename)
{
    ifstream mazeFile(filename);
    string row;
    int rowNumber = 0;

    initInterface("RoboChasin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, false);

    while (getline(mazeFile, row))
    {
        if (rowNumber < 1)
        {

            // First, we will separate the first line
            // that we find into the two numbers needed
            // to instatiate the maze (the number of rows
            // and the number of cols that it has).

            size_t separator = row.find('x');
            int numRows = stoi(row.substr(0, separator));
            int numCols = stoi(row.substr(separator + 1));

            // Updating our Game's maze.

            Maze maze(numRows, numCols);
            this->maze = maze;

            rowNumber++;
            continue;
            
        }
        
        for(int colNumber = 0; colNumber < row.size(); colNumber++)
        {
            if(row[colNumber] == '*' || row[colNumber] == '+')
            {

                // The board representation of our maze
                // starts on the second line of the opened file.
                // With that in mind, we instatiate the row of our
                // objects while subtracting '1' from it.

                Post post({rowNumber - 1, colNumber}, row[colNumber], renderer, "assets/box.png");
                if (post.isElectrified())
                    post.setTexture("assets/danger_box.png");
                maze.addPost(post);
            }

            else if(row[colNumber] == 'R' || row[colNumber] == 'r')
            {
                Robot robot({rowNumber - 1, colNumber}, renderer, "assets/robot_sheet.png");
                robots.push_back(robot);
            }

            else if(row[colNumber] == 'H' || row[colNumber] == 'h')
            {
                Player player({rowNumber - 1, colNumber}, renderer, "assets/human_sheet.png");
                this->player = player;
            }
            else if(row[colNumber] == 'O')
            {
                Gate gate ({rowNumber - 1, colNumber}, renderer, "assets/gate.png");
                maze.addGate(gate);
            }
        }

        rowNumber++;
    }

    mazeFile.close();

}

/******************************************************************************/

bool Game::validMove(Movement playerMove)
{
    // Retrieve human's coordinates.

    Position playerPos = player.getPosition();
    vector<Post> Posts = maze.getPosts();

    for (size_t i = 0; i < robots.size(); i++)
    {
        Position robotPos = robots[i].getPosition();

        if (robotPos.col == (playerPos.col + playerMove.dCol) && robotPos.row == (playerPos.row + playerMove.dRow))
        {
            char robotSymbol = robots[i].getSymbol();

            if (robotSymbol == 'r')
                return false;

            if (robotSymbol == 'R')
            {
                player.move(playerMove);
                player.setAsDead();
                return true;
            }
        }
    }

    for (size_t i = 0; i < Posts.size(); i++)
    {

        Position postPos = Posts[i].getPosition();

        if (postPos.col == (playerPos.col + playerMove.dCol) && postPos.row == (playerPos.row + playerMove.dRow))
        {
            char postType = Posts[i].getSymbol();
            if (postType == '+')
                return false;

            if (postType == '*')
            {
                player.setAsDead();
                return true;
            }
        }
    }

    player.move(playerMove);
    return true;

}

/******************************************************************************/

bool Game::play()
{
    vector<Post> Posts = maze.getPosts();
    vector<Gate> Gates = maze.getGates();

    while (player.isAlive() && running()) {

        handleEvents();
        updateRender();

        if (moveMade)
        {
            Position playerPos = player.getPosition();
            char postSymbol;

            for (size_t i = 0; i < robots.size(); i++) {

                if (robots[i].getSymbol() == 'R')

                    // In case our robot has been destroyed,
                    // do not move it. It must remain stuck
                    // until the end of the game. Only move
                    // robots that are alive.

                {
                    Position beforeRobotPos = robots[i].getPosition();
                    robots[i].seekHuman(playerPos);

                    for (size_t j = 0; j < Posts.size(); j++)
                    {

                        // Check each robot and see if it has
                        // collided with an electrified fence
                        // after moving it. Destroy it and move
                        // it back to its original place in case
                        // that happened.

                        postSymbol = Posts[j].getSymbol();

                        if (collide(robots[i], Posts[j]))
                        {
                            if (Posts[j].getSymbol() == '*')
                            {
                                // In case any robot moved to an
                                // electrified post's position, declare
                                // him dead on the spot it was before.

                                robots[i].setAsDead();
                                robots[i].setTexture("assets/robot_dead.png");
                            }

                            robots[i].setPosition(beforeRobotPos);
                        }

                    }

                    for (size_t j = 0; j < Gates.size(); j++)
                    {

                        // Apply that same logic to the exit gates,
                        // where if a robot moves towards them and
                        // actually collide with any of them, then
                        // it must be destroyed and put back in his
                        // original place.

                        Position gatePos = Gates[j].getPosition();
                        Position robotPos = robots[i].getPosition();

                        if (robotPos.row == gatePos.row && robotPos.col == gatePos.col)
                        {
                            robots[i].setPosition(beforeRobotPos);
                            robots[i].setTexture("assets/robot_dead.png");
                            robots[i].setAsDead();
                        }

                    }

                    for (size_t j = 0; j < robots.size(); j++)
                    {
                        if (i != j)

                            // We can't call the collide function
                            // on the same instance of a robot.

                            if (collide(robots[i], robots[j]))
                            {
                                robots[i].setAsDead();
                                robots[j].setAsDead();
                                robots[i].setTexture("assets/robot_dead.png");
                                robots[j].setTexture("assets/robot_dead.png");
                            }
                    }

                    // Check each robot and see if it has
                    // collided with the player after moving it.
                    // Declared him dead in case that happens.

                    if (collide(robots[i], player))
                    {
                        player.setAsDead();
                        break;
                    }

                }

            }

            if (collide(player, Posts)) {
                player.setAsDead();
                break;
            }

            if (reachedGate()) {

                // The game must end if the player
                // reaches one of the maze's exit gates.

                clean();
                return true;
            }
        }

        else
        {
            continue;
        }
    }

    clean();
    return false;
}

/******************************************************************************/

bool Game::reachedGate()
{
    vector<Gate> Gates = maze.getGates();
    Position playerPos = player.getPosition();

    for (size_t i = 0; i < Gates.size(); i++)
    {
        Position gatePos = Gates[i].getPosition();
        if (gatePos.row == playerPos.row && gatePos.col == playerPos.col)
            return true;
    }

    return false;
}

/******************************************************************************/

bool Game::collide(Robot &robot, Post& post)
{
    Position robotPos = robot.getPosition();
    Position postPos = post.getPosition();

    if (robotPos.row == postPos.row && robotPos.col == postPos.col)
    {
        return true;
    }

    return false;

}

/******************************************************************************/

bool Game::collide(Player &player, vector<Post>& Posts)
{
    for (int i = 0; i < Posts.size(); i++){
        Position playerPos = player.getPosition();
        Position postPos = Posts[i].getPosition();

        if (playerPos.row == postPos.row && playerPos.col == postPos.col)
        {
            return true;
        }
    }
    
    return false;

}

/******************************************************************************/

bool Game::collide(Robot &robot, Player& player)
{
    Position playerPos = player.getPosition();
    Position robotPos = robot.getPosition();

    if (playerPos.row == robotPos.row && playerPos.col == robotPos.col)
    {
            return true;
    }
    
    return false;

}

/******************************************************************************/

bool Game::collide(Robot &firstRobot, Robot &secondRobot)
{
    Position firstRobotPos = firstRobot.getPosition();
    Position secondRobotPos = secondRobot.getPosition();

    if (firstRobotPos.row == secondRobotPos.row && firstRobotPos.col == secondRobotPos.col)
    {
        return true;
    }

    return false;

}

/******************************************************************************/

void Game::initInterface(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Everything initialized..." << endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer working!" << endl;
        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }

}

/******************************************************************************/

void Game::handleEvents()
{
    Movement playerMove;

    moveMade = false;

    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {

    case SDL_QUIT:
        isRunning = false;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            isRunning = false;

        // In case the user moves, update
        // the player's position onto the screen
        // depending on the key that was pressed

        case SDLK_w:
            
            playerMove = { -1, 0 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_q:

            playerMove = { -1, -1 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_x:

            playerMove = { 1, 0 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_e:

            playerMove = { -1, 1 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_d:

            playerMove = { 0, 1 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_a:

            playerMove = { 0, -1 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_z:

            playerMove = { 1, -1 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_c:

            playerMove = { 1, 1 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        case SDLK_s:

            playerMove = { 0, 0 };
            if (validMove(playerMove))
                moveMade = true;
            break;

        default:
            if(!moveMade)
                cout << "Pick a valid move!" << endl;
            break;
        }

    default:
        break;

    }
}

/******************************************************************************/

void Game::updateRender()
{
    vector<Post> Posts = maze.getPosts();
    vector<Gate> Gates = maze.getGates();

    SDL_RenderClear(renderer);
    drawMap();

    for (size_t i = 0; i < robots.size(); i++)
    {
        if (robots[i].getSymbol() == 'r')

            robots[i].updateRender(false, player.getSourceRectangle(), player.getDestinationRectangle());
        else
            robots[i].updateRender(true, player.getSourceRectangle(), player.getDestinationRectangle(), 800, 2);
    }

    for (size_t i = 0; i < Posts.size(); i++)
    {
        Posts[i].updateRender(false, player.getSourceRectangle(), player.getDestinationRectangle());
    }

    for (size_t i = 0; i < Gates.size(); i++)
    {
        Gates[i].updateRender(false, player.getSourceRectangle(), player.getDestinationRectangle());
    }

    player.updateRender(true, player.getSourceRectangle(), player.getDestinationRectangle(), 200, 4);
    SDL_RenderPresent(renderer);
}

/******************************************************************************/

void Game::drawMap()
{
    SDL_Texture* tileTexture = TextureManager::LoadTexture("assets/tile.png", renderer);
    SDL_Rect sourceRectangle, destinationRectangle;

    int numCols = maze.getnumCols();
    int numRows = maze.getnumRows();

    for (int row = 0; row < numRows; row++)
    {
        for (int col = 0; col < numCols; col++)
        {
            sourceRectangle.h = 50;
            sourceRectangle.w = 50;
            sourceRectangle.x = 0;
            sourceRectangle.y = 0;

            destinationRectangle.h = 50;
            destinationRectangle.w = 50;
            destinationRectangle.x = col * 50;
            destinationRectangle.y = row * 50;

            SDL_RenderCopy(renderer, tileTexture, &sourceRectangle, &destinationRectangle);
        }

        
    }

}

/******************************************************************************/

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    cout << "Game cleaned!" << endl;
}

/******************************************************************************/

bool Game::running()
{
    return isRunning;
}