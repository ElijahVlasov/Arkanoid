class 'simple_block' (engine.block)

function simple_block:__init(box)
    engine.block.__init(self, box)
    sprite = system.create_sprite("textures/game/blocks/easyblock.png", system.sprite_type.static)
    self:set_sprite(sprite)
end

function simple_block:crash()
    return true
end
