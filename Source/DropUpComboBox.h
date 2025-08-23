#pragma once

#include <JuceHeader.h>

class DropUpComboBox : public juce::ComboBox
{
public:
    DropUpComboBox(const juce::String& name = {}) : juce::ComboBox(name) {}
    
    void showPopup() override
    {
        auto* popup = new juce::PopupMenu();
        popup->setLookAndFeel(&getLookAndFeel());
        
        // Add all items to the popup menu
        for (int i = 1; i <= getNumItems(); ++i)
        {
            popup->addItem(i, getItemText(i - 1), true, getSelectedId() == i);
        }
        
        // Calculate position for drop-up menu
        auto bounds = getScreenBounds();
        int menuHeight = getNumItems() * 30 + 10; // Approximate height
        
        // Position menu above the combo box
        juce::Rectangle<int> menuBounds(bounds.getX(), 
                                        bounds.getY() - menuHeight,
                                        bounds.getWidth(),
                                        menuHeight);
        
        // Show the menu and handle selection
        popup->showMenuAsync(juce::PopupMenu::Options()
                            .withTargetScreenArea(menuBounds)
                            .withPreferredPopupDirection(juce::PopupMenu::Options::PopupDirection::upwards),
                            [this](int result)
                            {
                                if (result > 0)
                                {
                                    setSelectedId(result);
                                }
                            });
    }
};