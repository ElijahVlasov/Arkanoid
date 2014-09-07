class 'metal_block' (engine.block)

function metal_block:__init(box)
    engine.block.__init(self, box)
    sprite = system.create_sprite("textures/game/blocks/metalblock.png", system.sprite_type.static)
    self:set_sprite(sprite)
    self.is_need_count = false
end

function metal_block:crash()
    return false
end
