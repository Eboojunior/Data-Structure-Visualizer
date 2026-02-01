int arr[5] = {1, 2, 3, 4, 5};
ImGui::Text("Tableau :");
ImGui::Columns(2);
ImGui::Text("Index"); ImGui::NextColumn();
ImGui::Text("Valeur"); ImGui::NextColumn();
for (int i = 0; i < 5; ++i) {
    ImGui::Text("%d", i); ImGui::NextColumn();
    ImGui::Text("%d", arr[i]); ImGui::NextColumn();
}
ImGui::Columns(1);
