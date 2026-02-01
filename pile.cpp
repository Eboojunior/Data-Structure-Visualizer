std::stack<int> stack;
stack.push(10);
stack.push(20);
stack.push(30);

ImGui::Text("Pile :");
while (!stack.empty()) {
    ImGui::Text("%d", stack.top());
    stack.pop();
}
