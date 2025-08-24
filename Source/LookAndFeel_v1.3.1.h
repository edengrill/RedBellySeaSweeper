#pragma once

#include <JuceHeader.h>

class SwoopLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SwoopLookAndFeel()
    {
        // Define colors matching the original design
        darkBackground = juce::Colour(0xff0c0d13);
        redAccent = juce::Colour(0xffd83427);
        lightGray = juce::Colour(0xffecebec);
        darkNavy = juce::Colour(0xff1a1d26);
    }
    
    // Custom rotary slider (knob) drawing - REMOVED GREY BORDER
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        auto radius = juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = x + width * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // Draw outer ring (white/light gray knob body)
        g.setColour(lightGray);
        g.fillEllipse(rx, ry, rw, rw);
        
        // Draw inner circle (slightly lighter shade)
        g.setColour(juce::Colour(0xffe0e0e0));
        g.fillEllipse(rx + 5, ry + 5, rw - 10, rw - 10);
        
        // Draw pointer (red indicator)
        juce::Path p;
        auto pointerLength = radius * 0.5f;
        auto pointerThickness = 2.5f;
        p.addRectangle(-pointerThickness * 0.5f, -radius + 8, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        
        g.setColour(redAccent);
        g.fillPath(p);
        
        // REMOVED: Grey circular border/shadow that was here
    }
    
    // Custom toggle button (power switch)
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
                          bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        auto bounds = button.getLocalBounds().toFloat();
        
        // Draw vertical pill background
        auto pillBounds = bounds.reduced(bounds.getWidth() * 0.3f, bounds.getHeight() * 0.1f);
        g.setColour(darkNavy);
        g.fillRoundedRectangle(pillBounds, pillBounds.getWidth() * 0.5f);
        
        // Draw inner shadow
        g.setColour(juce::Colours::black.withAlpha(0.3f));
        g.drawRoundedRectangle(pillBounds.reduced(1), pillBounds.getWidth() * 0.5f, 2.0f);
        
        // Draw handle
        auto handleSize = pillBounds.getWidth() * 0.8f;
        auto handleX = pillBounds.getCentreX() - handleSize * 0.5f;
        auto handleY = button.getToggleState() 
            ? pillBounds.getY() + 4.0f  // Top position when ON
            : pillBounds.getBottom() - handleSize - 4.0f; // Bottom position when OFF
        
        // Handle shadow/glow
        if (button.getToggleState())
        {
            g.setColour(redAccent.withAlpha(0.3f));
            g.fillEllipse(handleX - 3, handleY - 3, handleSize + 6, handleSize + 6);
        }
        
        // Handle
        g.setColour(button.getToggleState() ? redAccent : juce::Colour(0xff666666));
        g.fillEllipse(handleX, handleY, handleSize, handleSize);
    }
    
    // Custom combo box
    void drawComboBox(juce::Graphics& g, int width, int height, bool,
                      int, int, int, int, juce::ComboBox& box) override
    {
        auto cornerSize = 8.0f;
        juce::Rectangle<int> boxBounds(0, 0, width, height);
        
        g.setColour(juce::Colours::white);
        g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);
        
        g.setColour(redAccent);
        g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f), cornerSize, 2.0f);
        
        // Draw arrow pointing up (for drop-up menu)
        juce::Path p;
        p.addTriangle(width - 20, height * 0.55f,
                     width - 14, height * 0.45f,
                     width - 8, height * 0.55f);
        g.setColour(redAccent);
        g.fillPath(p);
        
        // Don't draw text here - let JUCE handle it via drawComboBoxTextWhenNothingSelected
    }
    
    void drawComboBoxTextWhenNothingSelected(juce::Graphics& g, juce::ComboBox& box, juce::Label&) override
    {
        g.setColour(redAccent);
        g.setFont(getComboBoxFont(box));
        
        auto textArea = box.getLocalBounds().reduced(10, 0).withTrimmedRight(30);
        g.drawFittedText(box.getText(), textArea, juce::Justification::centredLeft, 1);
    }
    
    void drawLabel(juce::Graphics& g, juce::Label& label) override
    {
        g.fillAll(label.findColour(juce::Label::backgroundColourId));
        
        if (!label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const juce::Font font(getLabelFont(label));
            
            g.setColour(label.findColour(juce::Label::textColourId).withMultipliedAlpha(alpha));
            g.setFont(font);
            
            auto textArea = getLabelBorderSize(label).subtractedFrom(label.getLocalBounds());
            
            g.drawFittedText(label.getText(), textArea, label.getJustificationType(),
                            juce::jmax(1, (int)(textArea.getHeight() / font.getHeight())),
                            label.getMinimumHorizontalScale());
            
            g.setColour(label.findColour(juce::Label::outlineColourId).withMultipliedAlpha(alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour(label.findColour(juce::Label::outlineColourId));
        }
        
        g.drawRect(label.getLocalBounds());
    }
    
    juce::Font getComboBoxFont(juce::ComboBox&) override
    {
        return juce::Font(14.0f).withStyle(juce::Font::plain);
    }
    
    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
                          bool isSeparator, bool isActive, bool isHighlighted,
                          bool isTicked, bool hasSubMenu, const juce::String& text,
                          const juce::String& shortcutKeyText,
                          const juce::Drawable* icon, const juce::Colour* textColour) override
    {
        auto bounds = area.toFloat();
        
        if (isHighlighted)
        {
            g.setColour(juce::Colour(0xff3d2b2b));
            g.fillRect(bounds);
        }
        
        g.setColour(isHighlighted ? redAccent : juce::Colour(0xffcccccc));
        g.setFont(14.0f);
        g.drawText(text, bounds.reduced(10, 0), juce::Justification::centredLeft);
    }
    
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override
    {
        g.fillAll(juce::Colour(0xff2d1b1b));
        g.setColour(redAccent);
        g.drawRect(0, 0, width, height, 1);
    }
    
private:
    juce::Colour darkBackground;
    juce::Colour redAccent;
    juce::Colour lightGray;
    juce::Colour darkNavy;
};