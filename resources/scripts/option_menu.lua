function change_language_click()
    local locales = {"en_US", "ru_RU", "uk_UA", "zh_CN"}
    local locale = system.get_locale()

    u=1
    for i = 1, #locales, 1 do
       if locales[i] == locale then
            break
       end
       u=u+1
    end

    if u == #locales then
        system.set_locale(locales[1])
    else
        system.set_locale(locales[u+1])
    end

end
