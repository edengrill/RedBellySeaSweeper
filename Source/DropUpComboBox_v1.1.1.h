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
        
        // Position menu above combo box with a small gap
        // Ensure it doesn't go above y=380 (just below the control panel)
        int menuY = screenBounds.getY() - menuHeight - 4;
        
        // Make sure menu doesn't overlap with control panel (which ends at y=380)
        // Control panel is at y=220-380, so menu should stop at y=385
        if (menuY < 385)
        {
            menuY = 385;
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