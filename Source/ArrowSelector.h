#pragma once
#include <JuceHeader.h>

class ArrowSelector : public juce::Component,
                       public juce::Button::Listener
{
public:
    ArrowSelector()
    {
        // Create up arrow button
        upButton.setButtonText("▲");
        upButton.addListener(this);
        upButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        upButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xffd83427));
        addAndMakeVisible(upButton);
        
        // Create down arrow button
        downButton.setButtonText("▼");
        downButton.addListener(this);
        downButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        downButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xffd83427));
        addAndMakeVisible(downButton);
        
        // Create display label
        display.setJustificationType(juce::Justification::centred);
        display.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
        display.setColour(juce::Label::backgroundColourId, juce::Colours::white);
        display.setColour(juce::Label::outlineColourId, juce::Colour(0xffd83427));
        addAndMakeVisible(display);
    }
    
    void addItem(const juce::String& item)
    {
        items.add(item);
        if (items.size() == 1)
        {
            currentIndex = 0;
            display.setText(items[0], juce::dontSendNotification);
        }
    }
    
    void setSelectedIndex(int index)
    {
        if (index >= 0 && index < items.size())
        {
            currentIndex = index;
            display.setText(items[currentIndex], juce::dontSendNotification);
        }
    }
    
    int getSelectedIndex() const { return currentIndex; }
    juce::String getSelectedText() const { return items[currentIndex]; }
    
    void resized() override
    {
        auto bounds = getLocalBounds();
        
        // Arrow buttons on the right side
        int arrowWidth = 20;
        auto arrowArea = bounds.removeFromRight(arrowWidth);
        
        upButton.setBounds(arrowArea.removeFromTop(bounds.getHeight() / 2));
        downButton.setBounds(arrowArea);
        
        // Display takes remaining space
        display.setBounds(bounds.reduced(1));
    }
    
    void buttonClicked(juce::Button* button) override
    {
        if (button == &upButton)
        {
            currentIndex = (currentIndex + 1) % items.size();
        }
        else if (button == &downButton)
        {
            currentIndex = (currentIndex - 1 + items.size()) % items.size();
        }
        
        display.setText(items[currentIndex], juce::dontSendNotification);
        
        if (onChange)
            onChange();
    }
    
    void paint(juce::Graphics& g) override
    {
        // Draw border
        g.setColour(juce::Colour(0xffd83427));
        g.drawRoundedRectangle(getLocalBounds().toFloat(), 3.0f, 2.0f);
    }
    
    std::function<void()> onChange;
    
private:
    juce::TextButton upButton;
    juce::TextButton downButton;
    juce::Label display;
    juce::StringArray items;
    int currentIndex = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ArrowSelector)
};