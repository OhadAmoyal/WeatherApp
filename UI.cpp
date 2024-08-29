#include "lib/imgui/imgui.h"
#include <map>
#include <string>

void ShowMapAsCards(const std::map<std::string, std::string>& data) {
    ImGui::Begin("Map Viewer"); // Start the ImGui window

    ImGui::Text("Click on a card to view details"); // A helpful title text

    ImGui::Spacing(); // Add some space

    // Loop through the map and create a card for each item
    for (const auto& item : data) {
        const std::string& key = item.first;
        const std::string& value = item.second;

        // Create a unique ID for each card using the key
        ImGui::PushID(key.c_str());

        // Create a colored button with the key as its label
        if (ImGui::Button(key.c_str(), ImVec2(120, 60))) {
            // When clicked, open a popup to display the value
            ImGui::OpenPopup("Card Value");
        }

        // Add hover animation effect by changing the color
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Click to view details");
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.7f, 0.3f, 1.0f); // Green when hovered
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.4f, 0.4f, 0.9f, 1.0f); // Blue when not hovered
        }

        // Render the popup for the clicked card
        if (ImGui::BeginPopup("Card Value")) {
            ImGui::Text("Value: %s", value.c_str());
            if (ImGui::Button("Close")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::PopID(); // End the unique ID for this card

        ImGui::SameLine(); // Keep the cards on the same line
    }

    ImGui::End(); // End the ImGui window
}