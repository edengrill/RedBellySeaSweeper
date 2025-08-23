#pragma once

#include <JuceHeader.h>

class DropUpComboBox : public juce::ComboBox
{
public:
    DropUpComboBox(const juce::String& name = {}) : juce::ComboBox(name) {}
    
    void showPopup() override
    {
        // Create popup menu
        juce::PopupMenu menu;
        menu.setLookAndFeel(&getLookAndFeel());
        
        // Add all items to the menu
        for (int i = 1; i <= getNumItems(); ++i)
        {
            menu.addItem(i, getItemText(i - 1), true, getSelectedId() == i);
        }
        
        // Get screen bounds of the combo box
        auto bounds = getScreenBounds();
        
        // Calculate menu height (more accurate calculation)
        int itemHeight = 25; // Typical height per menu item
        int menuPadding = 4; // Top and bottom padding
        int menuHeight = (getNumItems() * itemHeight) + (menuPadding * 2);
        
        // Force the menu to appear above the combo box
        // Set the target area to be above the combo box
        juce::Rectangle<int> targetArea(bounds.getX(), 
                                        bounds.getY() - menuHeight - 2, // 2px gap
                                        bounds.getWidth(),
                                        menuHeight);
        
        // Show the menu with upward direction forced
        auto options = juce::PopupMenu::Options()
            .withTargetScreenArea(targetArea)
            .withPreferredPopupDirection(juce::PopupMenu::Options::PopupDirection::upwards)
            .withMinimumWidth(bounds.getWidth())
            .withMaximumNumColumns(1)
            .withStandardItemHeight(itemHeight);
        
        // Show menu asynchronously and handle result
        menu.showMenuAsync(options, [this](int result)
        {
            if (result > 0)
            {
                setSelectedId(result);
            }
        });
    }
};