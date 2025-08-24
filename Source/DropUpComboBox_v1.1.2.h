#pragma once
#include <JuceHeader.h>

class DropUpComboBox : public juce::ComboBox
{
public:
    DropUpComboBox() : juce::ComboBox() {}
    
    void showPopup() override
    {
        juce::PopupMenu menu;
        
        // Add items to menu
        for (int i = 1; i <= getNumItems(); ++i)
        {
            menu.addItem(i, getItemText(i - 1), true, getSelectedId() == i);
        }
        
        // Calculate menu height (25px per item)
        int numItems = getNumItems();
        int menuHeight = numItems * 25;
        
        // Get the screen position of the combo box
        auto screenBounds = getScreenBounds();
        
        // Position menu to fit between control panel (y=380) and combo box (y=430)
        // The combo boxes are at y=430, control panel ends at y=380
        // So we have 50px of space for the menu
        
        // For better fit, let's position the menu just above the combo box
        // but ensure it stays within the white area (between y=380 and y=430)
        int menuY = screenBounds.getY() - menuHeight - 2;
        
        // Ensure menu doesn't go above the control panel area
        // Control panel ends at approximately y=380 in screen coordinates
        auto editorBounds = getTopLevelComponent()->getScreenBounds();
        int minY = editorBounds.getY() + 380; // Control panel bottom edge
        
        if (menuY < minY)
        {
            menuY = minY;
            // If menu doesn't fit, we may need to reduce height or scroll
        }
        
        auto menuPosition = juce::Rectangle<int>(screenBounds.getX(), 
                                                  menuY,
                                                  screenBounds.getWidth(), 
                                                  menuHeight);
        
        juce::PopupMenu::Options options = juce::PopupMenu::Options()
            .withTargetComponent(this)
            .withTargetScreenArea(menuPosition)
            .withMinimumWidth(getWidth())
            .withMaximumNumColumns(1)
            .withStandardItemHeight(25);
        
        // Force upward direction
        options = options.withPreferredPopupDirection(juce::PopupMenu::Options::PopupDirection::upwards);
        
        menu.showMenuAsync(options, [this](int result)
        {
            if (result != 0)
            {
                setSelectedId(result);
            }
        });
    }
    
    void mouseDown(const juce::MouseEvent& e) override
    {
        if (isEnabled())
        {
            auto localPoint = e.getEventRelativeTo(this).getPosition();
            
            // Check if click is within bounds
            if (getLocalBounds().contains(localPoint))
            {
                showPopup();
                return;
            }
        }
        
        ComboBox::mouseDown(e);
    }
    
    void mouseUp(const juce::MouseEvent& e) override
    {
        // Don't call parent to prevent default popup
    }
    
    bool hitTest(int x, int y) override
    {
        // Make entire area clickable
        return getLocalBounds().contains(x, y);
    }
};