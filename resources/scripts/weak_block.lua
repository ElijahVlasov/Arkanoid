class 'weak_block' (engine.block)

function weak_block:__init(box)
    engine.block.__init(self, box)
    self.hp=1

    self.last_sprite = system.create_sprite("textures/game/blocks/last_block.png", system.sprite_type.static)
    self.weak_sprite = system.create_sprite("textures/game/blocks/weak_block.png", system.sprite_type.static)

    self:set_sprite(self.weak_sprite)
end

function weak_block:crash()
    if self.hp == 0 then
        return true
    end

    self.hp = self.hp - 1

    self:set_sprite(self.last_sprite)

    return false
end
