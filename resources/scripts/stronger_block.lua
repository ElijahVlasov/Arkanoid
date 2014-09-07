class 'stronger_block' (weak_block)

function stronger_block:__init(box)
    weak_block.__init(self, box)
    self.hp=2

    self.stronger_sprite = system.create_sprite("textures/game/blocks/stronger_block.png", system.sprite_type.static)

    self:set_sprite(self.stronger_sprite)
end

function stronger_block:crash()
    if self.hp < 2 then
        return weak_block.crash(self)
    end

    self.hp = self.hp - 1

    self:set_sprite(self.weak_sprite)

    return false
end
