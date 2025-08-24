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
        
        // Calculate menu height more accurately
        int itemHeight = 24; // Standard menu item height
        int menuPadding = 8; // Total padding (top + bottom)
        int menuHeight = (getNumItems() * itemHeight) + menuPadding;
        
        // Position menu directly above the combo box with small gap
        // The menu should appear just above the combo box, not way up high
        juce::Rectangle<int> targetArea(
            bounds.getX(),                          // Same X position
            bounds.getY() - menuHeight - 4,         // Just above with 4px gap
            bounds.getWidth(),                       // Same width
            1                                        // Small height to force upward
        );
        
        // Configure options to ensure proper positioning
        auto options = juce::PopupMenu::Options()
            .withTargetComponent(this)  // Link to this component
            .withPreferredPopupDirection(juce::PopupMenu::Options::PopupDirection::upwards)
            .withMinimumWidth(bounds.getWidth())
            .withMaximumNumColumns(1)
            .withStandardItemHeight(itemHeight);
        
        // Show menu asynchronously
        menu.showMenuAsync(options, [this](int result)
        {
            if (result > 0)
            {
                setSelectedId(result, juce::sendNotificationSync);
            }
        });
    }
    
    // Override to ensure the combo box properly handles state
    void mouseDown(const juce::MouseEvent& e) override
    {
        // Only show popup if enabled and click is within bounds
        if (isEnabled() && e.eventComponent == this)
        {
            showPopup();
        }
    }
    
    // Prevent default popup behavior
    void mouseUp(const juce::MouseEvent&) override
    {
        // Do nothing - we handle everything in mouseDown
    }
};