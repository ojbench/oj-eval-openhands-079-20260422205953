#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v): val(v), next(nullptr) {}
};

struct LinkedList {
    Node* head = nullptr;

    Node* getKth(int k) {
        if (k <= 0) return nullptr;
        Node* p = head;
        int idx = 1;
        while (p && idx < k) {
            p = p->next;
            ++idx;
        }
        return (idx == k) ? p : nullptr;
    }

    int length() {
        int len = 0; Node* p = head; while (p) { ++len; p = p->next; } return len;
    }

    void initialize() {
        int n;
        if (scanf("%d", &n) != 1) return;
        int *a = new int[n];
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        Node* tail = nullptr;
        for (int i = 0; i < n; ++i) {
            Node* nd = new Node(a[i]);
            if (!head) {
                head = tail = nd;
            } else {
                tail->next = nd;
                tail = nd;
            }
        }
        delete[] a;
    }

    void insert(int i, int x) {
        Node* nd = new Node(x);
        if (i <= 0) {
            nd->next = head;
            head = nd;
            return;
        }
        Node* kth = getKth(i);
        if (!kth) {
            // append at end if i >= length? Find tail
            Node* p = head; Node* tail = nullptr;
            while (p) { tail = p; p = p->next; }
            if (!tail) {
                head = nd;
            } else {
                tail->next = nd;
            }
            return;
        }
        nd->next = kth->next;
        kth->next = nd;
    }

    void erase(int i) {
        if (!head || i <= 0) return;
        if (i == 1) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
            return;
        }
        Node* prev = getKth(i - 1);
        if (prev && prev->next) {
            Node* del = prev->next;
            prev->next = del->next;
            delete del;
        }
    }

    void swap_pairs() {
        if (!head || !head->next) return;
        Node* prev = nullptr;
        Node* cur = head;
        head = head->next;
        while (cur && cur->next) {
            Node* nxt = cur->next;
            Node* nextPair = nxt->next;
            if (prev) prev->next = nxt;
            nxt->next = cur;
            cur->next = nextPair;
            prev = cur;
            cur = nextPair;
        }
    }

    void moveback(int i, int x) {
        if (!head || i <= 0 || x <= 0) return;
        Node* prefix_tail = getKth(i);
        if (!prefix_tail || !prefix_tail->next) return; // nothing to move or i at end
        Node* old_head = head;
        Node* after_prefix = prefix_tail->next;
        Node* node_at_ix = getKth(i + x);
        if (!node_at_ix) return; // guard
        Node* node_at_ix_next = node_at_ix->next;
        // Detach prefix and insert after node_at_ix
        head = after_prefix;
        node_at_ix->next = old_head;
        prefix_tail->next = node_at_ix_next;
    }

    int query(int i) {
        Node* kth = getKth(i);
        return kth ? kth->val : 0;
    }

    void printAll() {
        Node* p = head;
        bool first = true;
        while (p) {
            if (!first) putchar(' ');
            first = false;
            printf("%d", p->val);
            p = p->next;
        }
        putchar('\n');
    }

    void ClearMemory() {
        Node* p = head;
        while (p) {
            Node* nxt = p->next;
            delete p;
            p = nxt;
        }
        head = nullptr;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LinkedList List;
    int m, op, i, x;
    List.initialize();
    if (scanf("%d", &m) != 1) {
        List.ClearMemory();
        return 0;
    }
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        } else if (op == 2) {
            scanf("%d", &i);
            List.erase(i);
        } else if (op == 3) {
            List.swap_pairs();
        } else if (op == 4) {
            scanf("%d%d", &i, &x);
            List.moveback(i, x);
        } else if (op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        } else if (op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}
