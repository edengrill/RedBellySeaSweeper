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
    
    // Override to make entire combo box clickable
    void mouseDown(const juce::MouseEvent& e) override
    {
        // Make the entire combo box area clickable, not just the arrow
        if (isEnabled())
        {
            // Check if click is anywhere within the combo box bounds
            auto localPoint = e.getEventRelativeTo(this).getPosition();
            if (getLocalBounds().contains(localPoint))
            {
                showPopup();
                return; // Don't call parent to prevent default behavior
            }
        }
        
        // For any other case, call parent
        ComboBox::mouseDown(e);
    }
    
    // Override to prevent default popup on mouse up
    void mouseUp(const juce::MouseEvent& e) override
    {
        // Check if this was a click on the combo box
        auto localPoint = e.getEventRelativeTo(this).getPosition();
        if (getLocalBounds().contains(localPoint))
        {
            // Do nothing - we already handled it in mouseDown
            return;
        }
        
        // For other cases, call parent
        ComboBox::mouseUp(e);
    }
    
    // Override to ensure whole area is interactive
    bool hitTest(int x, int y) override
    {
        // Make the entire rectangular area respond to clicks
        return getLocalBounds().contains(x, y);
    }
};