/*
 *
 */

#include <iostream>
#include <string>
#include <queue>
#include <array>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <optional>
#include <memory>
using namespace std;

struct Huffman {
    struct Node {
        std::uint32_t m_freq;
        std::optional<char> m_ch{};
        std::shared_ptr<Node> m_left{};
        std::shared_ptr<Node> m_right{};

        Node(std::uint32_t freq, std::optional<char> c = std::optional<char>{}) : m_freq(freq), m_ch(c) {}

        auto operator < (const Node& rhs) const noexcept {
            return this->m_freq < rhs.m_freq;
        }

        auto operator > (const Node& rhs) const noexcept {
            return this->m_freq > rhs.m_freq;
        }

    };

    explicit Huffman(const string& t) : m_text(t) {}

    void build_freq_dictionary() {
        for(auto&& c : m_text) {
            ++m_freqDict[c];
        }
    }

    void build_tree() {
        // build priority queue (minHeap) and then build tree
        for(auto&& [k, v] : m_freqDict) {
            m_heap.emplace(std::make_shared<Node>(v, k));
        }

        while(m_heap.size() > 1) {
            auto node1 = m_heap.top();
            m_heap.pop();
            auto node2 = m_heap.top();
            m_heap.pop();
            auto n = std::make_shared<Node>((node1->m_freq + node2->m_freq));
            n->m_left = node1;
            n->m_right = node2;
            m_heap.emplace(n);
        }
        m_root = m_heap.top();
        m_heap.pop();

        // build prefix codes
        build_prefix_codes();
    }

    void prefix_code_helper(std::shared_ptr<Node> node, string prefix_code) {
        if(node == nullptr) return;

        if(node->m_right == nullptr && node->m_left == nullptr) {
            m_encodingCodes[node->m_ch.value()] = prefix_code;
            m_decodingCodes[prefix_code] = node->m_ch.value();
        } else {
            prefix_code_helper(node->m_left, prefix_code + "0");
            prefix_code_helper(node->m_right, prefix_code + "1");
        }
    }

    void build_prefix_codes() {
        string prefix_code {};
        prefix_code_helper(m_root, prefix_code);
    }

    string encode() {
        string encoded_text{};
        for(auto&& c : m_text) {
            encoded_text += m_encodingCodes[c];
        }
        return encoded_text;
    }

    string decode(string encoded_text) {
        string decoded_text{};
        string prefix_code{};
        for(auto&& c : encoded_text) {
            prefix_code.append(1, c);
            if(m_decodingCodes.find(prefix_code) != m_decodingCodes.end()) {
                decoded_text.append(1, m_decodingCodes[prefix_code]);
                prefix_code.clear();
            }
        }
        return decoded_text;
    }

    struct Comparator {
        bool operator () (const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const noexcept {
            return *lhs > *rhs;
        }
    };

private:
    std::unordered_map<char, std::uint32_t> m_freqDict;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Comparator> m_heap;
    std::unordered_map<char, string> m_encodingCodes; // prefix codes
    std::unordered_map<string, char> m_decodingCodes; // prefix codes for decoding
    std::shared_ptr<Node> m_root{};
    string m_text;
};

int main() {
    string text = "kiyuycwvoey\nvghomwcje";

    Huffman hf{text};
    hf.build_freq_dictionary();
    hf.build_tree();

    auto encoded_text = hf.encode();
    cout << encoded_text << endl;

    auto decoded_text = hf.decode(encoded_text);
    cout << decoded_text << endl;

}