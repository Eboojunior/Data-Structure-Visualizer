struct Node {
    int value;
    Node* left;
    Node* right;
};

void draw_tree(Node* node) {
    if (node == nullptr) return;

    ImGui::Text("Node Value: %d", node->value);

    if (node->left) {
        ImGui::Text("Left child: %d", node->left->value);
    }

    if (node->right) {
        ImGui::Text("Right child: %d", node->right->value);
    }
}
