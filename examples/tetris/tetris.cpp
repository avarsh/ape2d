#include <ape/ape.h>
#include <map>
#include <random>
#include <array>

using namespace ape;

enum BlockTypes {
    L_SHAPE, T_SHAPE, INVERSE_L, S_SHAPE, STRAIGHT, SQUARE, INVERSE_S
};

// Can try to generate rotations using some maths tricks in the future
std::map<int, std::vector<std::array<Vec2i, 4>>> shapeCellMappings = {
    {
        L_SHAPE,  {{ Vec2i(0, 0), Vec2i(1, 0), Vec2i(2, 0), Vec2i(2, 1) },
                   { Vec2i(1, 0), Vec2i(1, 1), Vec2i(0, 2), Vec2i(1, 2) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(2, 1) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(0, 1), Vec2i(0, 2) }}
    },
    {
        T_SHAPE,  {{ Vec2i(0, 0), Vec2i(1, 0), Vec2i(2, 0), Vec2i(1, 1) },
                   { Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(1, 2) },
                   { Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(2, 1) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(0, 2) }}
    },
    {
        INVERSE_L,{{ Vec2i(0, 0), Vec2i(1, 0), Vec2i(2, 0), Vec2i(0, 1) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(1, 1), Vec2i(1, 2) },
                   { Vec2i(2, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(2, 1) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(0, 2), Vec2i(1, 2) }}
    },
    {
        S_SHAPE,  {{ Vec2i(1, 0), Vec2i(2, 0), Vec2i(0, 1), Vec2i(1, 1) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(1, 2) },
                   { Vec2i(1, 0), Vec2i(2, 0), Vec2i(0, 1), Vec2i(1, 1) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(1, 2) }}
    },
    {
        STRAIGHT, {{ Vec2i(0, 0), Vec2i(1, 0), Vec2i(2, 0), Vec2i(3, 0) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(0, 2), Vec2i(0, 3) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(2, 0), Vec2i(3, 0) },
                   { Vec2i(0, 0), Vec2i(0, 1), Vec2i(0, 2), Vec2i(0, 3) }}
    },
    {
        SQUARE,   {{ Vec2i(0, 0), Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1) }}
    },
    {
        INVERSE_S,{{ Vec2i(0, 0), Vec2i(1, 0), Vec2i(1, 1), Vec2i(2, 1) },
                   { Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(0, 2) },
                   { Vec2i(0, 0), Vec2i(1, 0), Vec2i(1, 1), Vec2i(2, 1) },
                   { Vec2i(1, 0), Vec2i(0, 1), Vec2i(1, 1), Vec2i(0, 2) }}
    },
};

// The board is 25x33 blocks
int columns = 25;
int rows = 33;
std::array<std::array<int, 33>, 25> board;
std::array<entity_t, 4> blockEntities;
std::array<std::array<int, 4>, 4> currentCollisionMask;
int blockSize = 24;

entity_t blockCamera;
entity_t blockLayer;
int currentRotation = 0;
int currentBlockType = -1;
Vec2i currentPosition;
Vec2i currentSize;
bool gameIsRunning = true;

void updateCollisionMask() {
    // Use the current block type to generate the collision mask
    std::array<Vec2i, 4> filledCells = shapeCellMappings[currentBlockType][currentRotation];
    std::array<int, 4> empty;
    empty.fill(0);
    currentCollisionMask.fill(empty);
    for(int i = 0; i < 4; i++) {
        currentCollisionMask[filledCells[i].x][filledCells[i].y] = blockEntities[i];
    }

    int yDims = 0;
    int xDims = 0;
    for(int xCoord = 0; xCoord < 4; xCoord++) {
        for(int yCoord = 0; yCoord < 4; yCoord++) {
            if(currentCollisionMask[xCoord][yCoord] != 0) {
                if(yCoord > yDims) {yDims = yCoord;}
                if(xCoord > xDims) {xDims = xCoord;}
            }
        }
    }
    yDims = (yDims + 1) * blockSize;
    xDims = (xDims + 1) * blockSize;
    currentSize = Vec2i(xDims, yDims);
}

void spawnBlock(int blockTexture) {
    // Generate block type
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> dist(0, 6);
    currentBlockType = dist(eng);

    for(int i = 0; i < 4; i++) {
        blockEntities[i] = world::createEntity();
        auto& sprite = world::addComponent<Sprite>(blockEntities[i], blockTexture);
        IntRect blockDims(currentBlockType * 26, 0, blockSize, blockSize);
        sprite.setSubRect(blockDims);
        auto& node = world::addComponent<Node>(blockEntities[i], blockLayer);
        auto& transform = world::getComponent<Transform>(blockEntities[i]);
        Vec2i cellPos = shapeCellMappings[currentBlockType][0][i];
        cellPos = cellPos * blockSize;
        transform.setPosition(cellPos.x + blockSize * 13, cellPos.y); // Position it roughly in the middle
    }

    currentPosition = Vec2i(blockSize * 13, 0);

    currentRotation = 0;
    updateCollisionMask();
}

void deleteRows(int y = 32) {

    int nextRow = y;
    bool currentRowFull = true;
    for(int x = 0; x < 25; x++) {
        if(board[x][y] == 0) {
            currentRowFull = false;
        }
    }

    if(currentRowFull) {
        for(int x = 0; x < 25; x++) {
            world::deleteEntity(board[x][y]);
        }

        decltype(board) newBoard;
        newBoard = board;

        for(int yCoord = 0; yCoord < y; yCoord++) {
            for(int xCoord = 0; xCoord < 25; xCoord++) {
                if(board[xCoord][yCoord] != 0) {
                    auto& transform = world::getComponent<Transform>(board[xCoord][yCoord]);
                    transform.move(0, blockSize);
                }
            }
        }

        for(int yCoord = 0; yCoord < y; yCoord++) {
            for(int xCoord = 0; xCoord < 25; xCoord++) {
                newBoard[xCoord][yCoord + 1] = board[xCoord][yCoord];
            }
        }

        board = newBoard;
    } else {
        nextRow = y - 1;
    }

    if(nextRow != -1) {
        deleteRows(nextRow);
    }
}

void setMasks() {
    Vec2i startingCell = currentPosition / blockSize;
    for(int xCoord = 0; xCoord < 4; xCoord++) {
        for(int yCoord = 0; yCoord < 4; yCoord++) {
            if(currentCollisionMask[xCoord][yCoord] != 0 &&
               xCoord + startingCell.x < 25 && yCoord + startingCell.y < 33) {
                board[xCoord + startingCell.x][yCoord + startingCell.y] = currentCollisionMask[xCoord][yCoord];
            }
        }
    }

    deleteRows();
}

enum Direction {
    LEFT,
    DOWN,
    RIGHT
};

bool checkForCollisions() {
    Vec2i startingCell = currentPosition / blockSize;
    for(int xCoord = 0; xCoord < 4; xCoord++) {
        for(int yCoord = 0; yCoord < 4; yCoord++) {
            if(xCoord + startingCell.x < 25 &&
               yCoord + startingCell.y < 33) {
                if(board[xCoord + startingCell.x][yCoord + startingCell.y] != 0 &&
                   currentCollisionMask[xCoord][yCoord] != 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool checkForCollisions(int dir) {
    // Check for collision in a direction
    int xOffset = 0;
    int yOffset = 0;
    if(dir == DOWN) { yOffset = 1; }
    if(dir == LEFT) { xOffset = -1; }
    if(dir == RIGHT) { xOffset = 1; }

    currentPosition.x += xOffset * blockSize;
    currentPosition.y += yOffset * blockSize;

    bool isColliding = checkForCollisions();

    currentPosition.x -= xOffset * blockSize;
    currentPosition.y -= yOffset * blockSize;

    return isColliding;
}

bool isOutOfBounds(int dir) {
    int xOffset = 0;
    int yOffset = 0;
    if(dir == DOWN) { yOffset = 1; }
    if(dir == LEFT) { xOffset = -1; }
    if(dir == RIGHT) { xOffset = 1; }

    Vec2i newPosition = currentPosition + Vec2i(xOffset, yOffset) * blockSize;
    bool outOfBounds = false;

    if(newPosition.x + currentSize.x > 600 ||
       newPosition.y + currentSize.y > 792 ||
       newPosition.x < 0) {
        outOfBounds = true;
    }

    return outOfBounds;
}

void rotateCurrentBlock() {

    currentRotation = currentRotation == 3 ? 0 : currentRotation + 1;
    updateCollisionMask();
    // Check for collision or out of bounds
    bool isColliding = checkForCollisions();
    bool xOutOfBounds = (currentPosition.x + currentSize.x > 600);
    bool yOutOfBounds = (currentPosition.y + currentSize.y > 792);

    if(checkForCollisions() || xOutOfBounds || yOutOfBounds) {
          currentRotation = currentRotation == 0 ? 3 : currentRotation - 1;
          updateCollisionMask();
          return;
    }

    for(int i = 0; i < 4; i++) {
        auto& transform = world::getComponent<Transform>(blockEntities[i]);
        auto pos = (shapeCellMappings[currentBlockType][currentRotation][i] * blockSize) + currentPosition;
        transform.setPosition(pos.x, pos.y);
    }
}

bool moveIfPossible(int dir) {
    int xOffset = 0;
    int yOffset = 0;
    if(dir == DOWN) { yOffset = 1; }
    if(dir == LEFT) { xOffset = -1; }
    if(dir == RIGHT) { xOffset = 1; }
    Vec2f offset(xOffset * blockSize, yOffset * blockSize);
    bool colliding = checkForCollisions(dir);
    bool outOfBounds = isOutOfBounds(dir);
    if(!colliding && !outOfBounds) {
        for(int i = 0; i < 4; i++) {
            auto& transform = world::getComponent<Transform>(blockEntities[i]);
            transform.move(offset);
        }
        currentPosition += Vec2i(offset.x, offset.y);

        return true;
    }

    return false;
}

int main() {
    // Initialisation
    engine::init();
    window::create(600, 792, "Tetris");

    // Initialise the board to be empty
    std::array<int, 33> empty;
    empty.fill(0);
    board.fill(empty);

    // Create a camera
    blockCamera = world::createEntity();
    world::addComponent<Camera>(blockCamera);

    blockLayer = world::createEntity();
    auto& layerNode = world::addComponent<Node>(blockLayer, scene::rootNode);
    layerNode.setCamera(blockCamera);

    // Load block spritesheet
    auto blockSheet = textureStore::loadTexture("./examples/tetris/individual_blocks.png");
    if(blockSheet == -1) {
        return 1;
    }

    // Setup inputs
    auto& context = input::ContextManager::createContext(0);
    auto actionData = input::ActionData(
        input::Device::KEYBOARD,
        input::ActionType::KEY_PRESS,
        input::Keys::Space
    );

    context.addActionCallback(actionData, [=](){
        rotateCurrentBlock();
    });

    auto movement = input::ActionData(
        input::Device::KEYBOARD,
        input::ActionType::KEY_PRESS,
        input::Keys::Left
    );

    context.addActionCallback(movement, [&](){
        moveIfPossible(LEFT);
    });

    movement.data = input::Keys::Right;
    context.addActionCallback(movement, [&](){
        moveIfPossible(RIGHT);
    });

    movement.data = input::Keys::Down;
    context.addActionCallback(movement, [&](){
        moveIfPossible(DOWN);
    });

    movement.data = input::Keys::Enter;
    context.addActionCallback(movement, [&](){
        while(moveIfPossible(DOWN)) { }
    });

    spawnBlock(blockSheet);

    double timer = 0;
    float pause = 1.f;
    engine::addSimulationCode([&](double dt){
        timer += dt;
        if(timer >= pause && gameIsRunning) {
            if(!moveIfPossible(DOWN)) {
                setMasks();
                spawnBlock(blockSheet);
            }
            timer -= pause;
        }
    });

    while(engine::isRunning()) {
        window::clear(Colors::Slate);
        engine::update();

        // Check for loss
        for(int x = 0; x < 25; x++) {
            if(board[x][0] != 0) {
                gameIsRunning = false;
            }
        }

        window::display();
    }

    return 0;
}
