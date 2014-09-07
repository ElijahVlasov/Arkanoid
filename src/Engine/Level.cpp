#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/ref.hpp>

#include <lua.hpp>
#include <luabind/adopt_policy.hpp>
#include <luabind/luabind.hpp>

#include <Engine/Game.hpp>
#include <Engine/Level.hpp>

#include <Utils/assert.hpp>
#include <Utils/ResourceManager.hpp>
#include <Utils/SingletonPointer.hpp>
#include <Utils/Lua.hpp>

#include <Utils/Audio/Sound.hpp>

#include <Utils/Graphics/GraphicsManager.hpp>
#include <Utils/Graphics/Texture.hpp>

using namespace std;

using namespace Engine;

using namespace Utils;
using namespace Utils::Audio;
using namespace Utils::Graphics;

const char* Level::LEVEL_SIGNATURE = "LVL";



Level::Level(const string& data) throw(invalid_argument, runtime_error):
    game_(Game::getInstance()),
    lua_(Lua::getInstance()),
    blockWidth_(0),
    blockHeight_(0),
    blocksCount_(0)
{

    ASSERT(
        !data.empty(),
        invalid_argument("data")
    );

    ASSERT(
        (memcmp(data.data(), LEVEL_SIGNATURE, 3) == 0),
        invalid_argument("data")
    );

    SingletonPointer<ResourceManager> resourceManager = ResourceManager::getInstance();

    const Level::LEVEL* levelStruct = reinterpret_cast<const Level::LEVEL*>(data.data());

    sound_          = resourceManager->getResource<Sound>(levelStruct->music);
    background_     = resourceManager->getResource<Texture>(levelStruct->background);

    rect_.min_corner().x(levelStruct->x);
    rect_.min_corner().y(levelStruct->y);
    rect_.max_corner().x(levelStruct->x + levelStruct->width);
    rect_.max_corner().y(levelStruct->y + levelStruct->height);

    const_cast<unsigned int&>(blockWidth_)  = levelStruct->blockWidth;
    const_cast<unsigned int&>(blockHeight_) = levelStruct->blockHeight;

    const char* blocks = data.data() + levelStruct->blocksOffset;

    size_t rowSize = levelStruct->cols * 80; // Вычисляем длину строки(Количество столбцов * максимальный размер имени блока)

    blocks_.resize(levelStruct->rows);

    lua_State* L = lua_->getLuaState_newThread();

    for(unsigned int i = 0; i < levelStruct->rows; i++) {

        blocks_[i].resize(levelStruct->cols);

        for(unsigned int j = 0; j < levelStruct->cols; j++) {

            char block[80];
            const char* p = blocks + rowSize * i + j * 80; // Находим текущий блок

            if(*p == '\0') {
                continue;
            }

            strncpy(block, p, 80);

            // Вычисляем текущее положение блока:

            float x = levelStruct->x + levelStruct->blockWidth  * j;
            float y = levelStruct->y + levelStruct->blockHeight * i;

            GeometryDefines::Box blockBox(
                                    GeometryDefines::Point(x, y),
                                    GeometryDefines::Point(x + levelStruct->blockWidth, y + levelStruct->blockHeight)
                                 );

            // Из Lua получаем блок:
            luabind::object blockObject = luabind::call_function< luabind::object >(L, block, boost::cref(blockBox));

            ASSERT(
                blockObject.is_valid(),
                runtime_error("Can't create block object")
            );

            ASSERT(
                (luabind::type(blockObject) != LUA_TNIL),
                runtime_error("Can't create block object")
            );

            Block* b = luabind::object_cast<Block*>(blockObject, luabind::adopt(luabind::result));

            blocks_[i][j] = boost::shared_ptr<Block>(b);

            if(b->isNeedCount()) {
                blocksCount_++;
            }

        }

    }

}



list< boost::shared_ptr<Block> > Level::getBlocksInBox(GeometryDefines::Box box) const {

    list< boost::shared_ptr<Block> > blocksInBox;

    // Если бокс левее
    if(box.max_corner().x() < rect_.min_corner().x()) {
        return blocksInBox;
    }

    // Если бокс ниже
    if(box.max_corner().y() < rect_.min_corner().y()) {
        return blocksInBox;
    }

    // Если бокс правее
    if(box.min_corner().x() > rect_.max_corner().x()) {
        return blocksInBox;
    }

    // Если бокс выше
    if(box.min_corner().y() > rect_.max_corner().y()) {
        return blocksInBox;
    }

    if(box.min_corner().x() < rect_.min_corner().x()) {
        box.min_corner().x(rect_.min_corner().x());
    }

    if(box.min_corner().y() < rect_.min_corner().y()) {
        box.min_corner().y(rect_.min_corner().y());
    }

    if(box.max_corner().x() > rect_.max_corner().x()) {
        box.max_corner().x(rect_.max_corner().x());
    }

    if(box.max_corner().y() > rect_.max_corner().y()) {
        box.max_corner().y(rect_.max_corner().y());
    }

    unsigned int rowStart, rowEnd, colStart, colEnd;

    colStart = (unsigned int) (box.min_corner().x() - rect_.min_corner().x()) / blockWidth_;
    colEnd   = (unsigned int) (box.max_corner().x() - rect_.min_corner().x()) / blockWidth_;

    rowStart = (unsigned int) (box.min_corner().y() - rect_.min_corner().y()) / blockHeight_;
    rowEnd   = (unsigned int) (box.max_corner().y() - rect_.min_corner().y()) / blockHeight_;

    if(colEnd > blocks_[0].size() - 1) {
        colEnd = blocks_[0].size() - 1;
    }

    if(rowEnd > blocks_.size() - 1) {
        rowEnd = blocks_.size() - 1;
    }

    for(unsigned int i = rowStart; i <= rowEnd; i++) {

        for(unsigned int j = colStart; j <= colEnd; j++) {

            if(blocks_[i][j] == 0) {
                continue;
            }

            blocksInBox.push_back(blocks_[i][j]);

        }

    }

    return blocksInBox;

}



size_t Level::getBlocksCount() const {

    return blocksCount_;

}



const boost::shared_ptr<Sound>& Level::getSound() const {

    return sound_;

}



void Level::crashBlock(const boost::shared_ptr<Block>& block) {

    if(block == 0) {
        return;
    }

    float x = block->getRect().min_corner().x();
    float y = block->getRect().min_corner().y();

    unsigned int j = static_cast<unsigned int>((x - rect_.min_corner().x()) / blockWidth_);
    unsigned int i = static_cast<unsigned int>((y - rect_.min_corner().y()) / blockHeight_);

    if(blocks_[i][j]->crash()) {

        if(blocks_[i][j]->isNeedCount()) {
            blocksCount_--;
        }

        blocks_[i][j] = 0;

    }

}



void Level::draw() {

    GraphicsManager::DrawTexture(
        GeometryDefines::BoxI(
            GeometryDefines::PointI(0, 0),
            GeometryDefines::PointI(game_->getScreenWidth(), game_->getScreenHeight())
        ),
        *background_
    );

    unsigned int rows, cols;

    rows = blocks_.size();

    for(unsigned int i = 0; i < rows; i++) {

        cols = blocks_[i].size();

        for(unsigned int j = 0; j < cols; j++) {

            if(blocks_[i][j] == 0) {
                continue;
            }

            blocks_[i][j]->draw();

        }

    }

}



void Level::clear() {

    blocksCount_ = 0;

    unsigned int rows, cols;

    rows = blocks_.size();

    for(unsigned int i = 0; i < rows; i++) {

        cols = blocks_[i].size();

        for(unsigned int j = 0; j < cols; j++) {

            if(blocks_[i][j] == 0) {
                continue;
            }

            if(blocks_[i][j]->isNeedCount()) {
                blocks_[i][j] = 0;
            }

        }

    }

}
