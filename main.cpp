#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <functional>
#include <filesystem>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Utils {
public:
    static void clearScreen() {
        system("clear");
    }
    
    static void printHeader(const string& title) {
        cout << "\n╔══════════════════════════════════════════════════════════╗\n";
        cout << "║  " << left << setw(46) << title << "║\n";
        cout << "╚══════════════════════════════════════════════════════════╝\n";
    }
    
    static void printSuccess(const string& msg) {
        cout << "\033[32m✓ " << msg << "\033[0m\n";
    }
    
    static void printError(const string& msg) {
        cout << "\033[31m✗ " << msg << "\033[0m\n";
    }
    
    static void printInfo(const string& msg) {
        cout << "\033[36mℹ " << msg << "\033[0m\n";
    }
    
    static string getTimestamp() {
        auto now = chrono::system_clock::now();
        auto time = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

class TemplateGenerator {
private:
    string createFastIOTemplate() {
        return R"(#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

void solve() {
}

int32_t main() {
    fastIO();
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
})";
    }
    
    string createBinarySearchTemplate() {
        return R"(#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

bool check(int mid) {
    return true;
}

void solve() {
    int lo = 0, hi = 1e18, ans = -1;
    while(lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if(check(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << endl;
}

int32_t main() {
    fastIO();
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
})";
    }
    
    string createDSUTemplate() {
        return R"(#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

class DSU {
private:
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if(rx != ry) {
            if(rank[rx] < rank[ry])
                parent[rx] = ry;
            else if(rank[rx] > rank[ry])
                parent[ry] = rx;
            else {
                parent[ry] = rx;
                rank[rx]++;
            }
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
}

int32_t main() {
    fastIO();
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
})";
    }
    
    string createPrefixSlidingTemplate() {
        return R"(#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    
    vector<int> prefix(n + 1, 0);
    for(int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    
    int windowSum = 0;
    for(int i = 0; i < k; i++) windowSum += arr[i];
    int maxSum = windowSum;
    
    for(int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, windowSum);
    }
    
    cout << maxSum << endl;
}

int32_t main() {
    fastIO();
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
})";
    }
    
    string createGraphTraversalTemplate() {
        return R"(#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

class Graph {
private:
    int V;
    vector<vector<int>> adj;
public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> st;
        st.push(start);
        
        while(!st.empty()) {
            int u = st.top();
            st.pop();
            
            if(!visited[u]) {
                visited[u] = true;
                cout << u << " ";
                
                for(int v : adj[u]) {
                    if(!visited[v]) {
                        st.push(v);
                    }
                }
            }
        }
        cout << endl;
    }
    
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";
            
            for(int v : adj[u]) {
                if(!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
};

void solve() {
}

int32_t main() {
    fastIO();
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
})";
    }
    
public:
    void generateTemplate(const string& type) {
        string templateType = type;
        
        while(!templateType.empty() && isspace(templateType.back())) {
            templateType.pop_back();
        }
        while(!templateType.empty() && isspace(templateType.front())) {
            templateType.erase(0, 1);
        }
        
        map<string, string> templates;
        templates["fastio"] = createFastIOTemplate();
        templates["binarysearch"] = createBinarySearchTemplate();
        templates["dsu"] = createDSUTemplate();
        templates["prefix"] = createPrefixSlidingTemplate();
        templates["graph"] = createGraphTraversalTemplate();
        
        if(templates.find(templateType) != templates.end()) {
            string filename = templateType + "_template.cpp";
            ofstream file(filename.c_str());
            if(file.is_open()) {
                file << templates[templateType];
                file.close();
                Utils::printSuccess("Template generated: " + filename);
            } else {
                Utils::printError("Failed to create template file");
            }
        } else {
            Utils::printError("Unknown template type: '" + templateType + "'");
        }
    }
    
    void listTemplates() {
        Utils::printInfo("Available templates:");
        cout << "  1. fastio - Fast I/O template\n";
        cout << "  2. binarysearch - Binary search template\n";
        cout << "  3. dsu - Disjoint Set Union template\n";
        cout << "  4. prefix - Prefix Sum & Sliding Window template\n";
        cout << "  5. graph - Graph traversal template\n";
    }
};

class TestCaseGenerator {
private:
    mt19937 rng;
    
public:
    TestCaseGenerator() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}
    
    void generateArrayTest() {
        int n, minVal, maxVal;
        cout << "Enter array size: ";
        cin >> n;
        cout << "Enter min value: ";
        cin >> minVal;
        cout << "Enter max value: ";
        cin >> maxVal;
        
        uniform_int_distribution<int> dist(minVal, maxVal);
        
        ofstream file("test_input.txt");
        if(file.is_open()) {
            file << n << "\n";
            for(int i = 0; i < n; i++) {
                file << dist(rng);
                if(i != n-1) file << " ";
            }
            file << "\n";
            file.close();
            Utils::printSuccess("Array test case generated in test_input.txt");
        }
    }
    
    void generateGraphTest() {
        int V, E;
        cout << "Enter number of vertices: ";
        cin >> V;
        cout << "Enter number of edges: ";
        cin >> E;
        
        uniform_int_distribution<int> vertDist(0, V-1);
        
        ofstream file("graph_input.txt");
        if(file.is_open()) {
            file << V << " " << E << "\n";
            set<pair<int,int>> edges;
            
            for(int i = 0; i < E; i++) {
                int u, v;
                do {
                    u = vertDist(rng);
                    v = vertDist(rng);
                } while(u == v || edges.count({u,v}) || edges.count({v,u}));
                
                edges.insert({u,v});
                file << u << " " << v << "\n";
            }
            file.close();
            Utils::printSuccess("Graph test case generated in graph_input.txt");
        }
    }
    
    void generateStringTest() {
        int len;
        cout << "Enter string length: ";
        cin >> len;
        
        uniform_int_distribution<int> charDist(0, 25);
        
        ofstream file("string_input.txt");
        if(file.is_open()) {
            for(int i = 0; i < len; i++) {
                file << char('a' + charDist(rng));
            }
            file << "\n";
            file.close();
            Utils::printSuccess("String test case generated in string_input.txt");
        }
    }
    
    void generateMatrixTest() {
        int rows, cols, minVal, maxVal;
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of columns: ";
        cin >> cols;
        cout << "Enter min value: ";
        cin >> minVal;
        cout << "Enter max value: ";
        cin >> maxVal;
        
        uniform_int_distribution<int> dist(minVal, maxVal);
        
        ofstream file("matrix_input.txt");
        if(file.is_open()) {
            file << rows << " " << cols << "\n";
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    file << dist(rng);
                    if(j == cols-1) file << "\n";
                    else file << " ";
                }
            }
            file.close();
            Utils::printSuccess("Matrix test case generated in matrix_input.txt");
        }
    }
    
    void generateCustomTest() {
        cout << "Enter custom input (end with Ctrl+D on new line):\n";
        ofstream file("custom_input.txt");
        if(file.is_open()) {
            string line;
            while(getline(cin, line)) {
                file << line << "\n";
            }
            file.close();
            Utils::printSuccess("Custom test case saved to custom_input.txt");
        }
    }
};

class OutputComparator {
private:
    string readFile(const string& filename) {
        ifstream file(filename);
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        if(first == string::npos) return "";
        return str.substr(first, last - first + 1);
    }
    
    vector<string> splitLines(const string& str) {
        vector<string> lines;
        stringstream ss(str);
        string line;
        while(getline(ss, line)) {
            string trimmed = trim(line);
            if(!trimmed.empty()) {
                lines.push_back(trimmed);
            }
        }
        return lines;
    }
    
public:
    void compareOutputs(const string& file1, const string& file2) {
        string content1 = readFile(file1);
        string content2 = readFile(file2);
        
        vector<string> lines1 = splitLines(content1);
        vector<string> lines2 = splitLines(content2);
        
        Utils::printHeader("Output Comparison");
        
        if(lines1 == lines2) {
            Utils::printSuccess("Outputs match perfectly!");
            cout << "\nBoth files produced identical output.\n";
        } else {
            Utils::printError("Outputs differ!");
            
            size_t minLines = min(lines1.size(), lines2.size());
            bool differencesFound = false;
            
            for(size_t i = 0; i < minLines; i++) {
                if(lines1[i] != lines2[i]) {
                    differencesFound = true;
                    cout << "\nLine " << i+1 << ":\n";
                    cout << "  File 1: " << lines1[i] << "\n";
                    cout << "  File 2: " << lines2[i] << "\n";
                }
            }
            
            if(lines1.size() != lines2.size()) {
                differencesFound = true;
                cout << "\nLine count mismatch:\n";
                cout << "  File 1: " << lines1.size() << " lines\n";
                cout << "  File 2: " << lines2.size() << " lines\n";
            }
            
            if(!differencesFound && minLines > 0) {
                cout << "\nNo line-by-line differences found.\n";
            }
        }
    }
    
    void compareWithBruteForce(const string& bruteFile, const string& optFile) {
        cout << "\nComparing brute-force vs optimized solution...\n";
        compareOutputs(bruteFile, optFile);
    }
};

class PerformanceAnalyzer {
private:
    chrono::high_resolution_clock::time_point start;
    
public:
    void startTimer() {
        start = chrono::high_resolution_clock::now();
    }
    
    long long stopTimer() {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        return duration.count();
    }
    
    void measureExecutionTime(const string& executable, const string& inputFile) {
        Utils::printHeader("Performance Analysis");
        
        string command = "./" + executable + " < " + inputFile + " > temp_output.txt";
        
        startTimer();
        int result = system(command.c_str());
        long long microSec = stopTimer();
        
        if(result == 0) {
            double milliSec = microSec / 1000.0;
            double seconds = milliSec / 1000.0;
            
            cout << "\nExecution Time:\n";
            cout << "  " << microSec << " microseconds\n";
            cout << "  " << fixed << setprecision(3) << milliSec << " milliseconds\n";
            cout << "  " << fixed << setprecision(6) << seconds << " seconds\n";
            
            if(microSec < 1000) {
                Utils::printSuccess("Excellent performance!");
            } else if(microSec < 10000) {
                Utils::printSuccess("Good performance!");
            } else if(microSec < 100000) {
                Utils::printInfo("Acceptable performance");
            } else {
                Utils::printError("Needs optimization");
            }
        } else {
            Utils::printError("Execution failed!");
        }
    }
    
   /* void analyzeComplexity(int n, long long timeMicroSec) {
        cout << "\nComplexity Analysis:\n";
        cout << "  Input size: " << n << "\n";
        cout << "  Measured time: " << timeMicroSec << " μs\n";
        
        if(n <= 100 && timeMicroSec < 1000) {
            cout << "  Estimated complexity: O(n!) or O(2^n) with small n\n";
        } else if(n <= 1000 && timeMicroSec < 10000) {
            cout << "  Estimated complexity: O(n^2)\n";
        } else if(n <= 100000 && timeMicroSec < 100000) {
            cout << "  Estimated complexity: O(n log n)\n";
        } else if(n <= 10000000 && timeMicroSec < 1000000) {
            cout << "  Estimated complexity: O(n)\n";
        } else {
            cout << "  Estimated complexity: O(log n) or O(1)\n";
        }
    }*/
};

class GraphUtils {
private:
    class DSU {
    private:
        vector<int> parent, rank;
    public:
        DSU(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for(int i = 0; i < n; i++) parent[i] = i;
        }
        
        int find(int x) {
            if(parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        
        void unite(int x, int y) {
            int rx = find(x), ry = find(y);
            if(rx != ry) {
                if(rank[rx] < rank[ry])
                    parent[rx] = ry;
                else if(rank[rx] > rank[ry])
                    parent[ry] = rx;
                else {
                    parent[ry] = rx;
                    rank[rx]++;
                }
            }
        }
        
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
    };
    
    class BridgeFinder {
    private:
        int V, time;
        vector<vector<int>> adj;
        vector<int> disc, low;
        vector<bool> visited;
        vector<pair<int,int>> bridges;
        
        void dfs(int u, int parent) {
            visited[u] = true;
            disc[u] = low[u] = ++time;
            
            for(int v : adj[u]) {
                if(!visited[v]) {
                    dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    
                    if(low[v] > disc[u]) {
                        bridges.push_back({u, v});
                    }
                } else if(v != parent) {
                    low[u] = min(low[u], disc[v]);
                }
            }
        }
        
    public:
        BridgeFinder(int V) : V(V), time(0) {
            adj.resize(V);
            disc.resize(V);
            low.resize(V);
            visited.resize(V, false);
        }
        
        void addEdge(int u, int v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<pair<int,int>> findBridges() {
            bridges.clear();
            for(int i = 0; i < V; i++) {
                if(!visited[i]) {
                    dfs(i, -1);
                }
            }
            return bridges;
        }
    };
    
public:
    void checkConnectivity() {
        Utils::printHeader("Connectivity Checker (DSU)");
        
        int V, E;
        cout << "Enter number of vertices: ";
        cin >> V;
        cout << "Enter number of edges: ";
        cin >> E;
        
        DSU dsu(V);
        
        cout << "Enter edges (u v):\n";
        for(int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            dsu.unite(u, v);
        }
        
        int components = 0;
        for(int i = 0; i < V; i++) {
            if(dsu.find(i) == i) components++;
        }
        
        cout << "\nResults:\n";
        cout << "  Number of connected components: " << components << "\n";
        
        if(components == 1) {
            Utils::printSuccess("The graph is fully connected!");
        } else {
            Utils::printInfo("The graph has " + to_string(components) + " components");
        }
        
        int q1, q2;
        cout << "\nCheck connectivity between two vertices:\n";
        cout << "Enter u v: ";
        cin >> q1 >> q2;
        
        if(dsu.connected(q1, q2)) {
            Utils::printSuccess("Vertices " + to_string(q1) + " and " + to_string(q2) + " are connected");
        } else {
            Utils::printError("Vertices " + to_string(q1) + " and " + to_string(q2) + " are not connected");
        }
    }
    
    void findBridges() {
        Utils::printHeader("Bridge Detection (Tarjan's Algorithm)");
        
        int V, E;
        cout << "Enter number of vertices: ";
        cin >> V;
        cout << "Enter number of edges: ";
        cin >> E;
        
        BridgeFinder finder(V);
        
        cout << "Enter edges (u v):\n";
        for(int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            finder.addEdge(u, v);
        }
        
        auto bridges = finder.findBridges();
        
        cout << "\nResults:\n";
        if(bridges.empty()) {
            Utils::printSuccess("No bridges found in the graph!");
        } else {
            cout << "Bridges found:\n";
            for(auto& bridge : bridges) {
                cout << "  " << bridge.first << " -- " << bridge.second << "\n";
            }
            
            if(bridges.size() == 1) {
                Utils::printInfo("This graph has 1 bridge");
            } else {
                Utils::printInfo("This graph has " + to_string(bridges.size()) + " bridges");
            }
        }
    }
    
    void shortestPathDemo() {
        Utils::printHeader("Shortest Path (Dijkstra's Algorithm)");
        
        int V, E;
        cout << "Enter number of vertices: ";
        cin >> V;
        cout << "Enter number of edges: ";
        cin >> E;
        
        vector<vector<pair<int,int>>> adj(V);
        
        cout << "Enter edges (u v weight):\n";
        for(int i = 0; i < E; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        int source;
        cout << "Enter source vertex: ";
        cin >> source;
        
        vector<int> dist(V, INT_MAX);
        dist[source] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, source});
        
        while(!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if(d > dist[u]) continue;
            
            for(auto& [v, w] : adj[u]) {
                if(dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        cout << "\nShortest distances from vertex " << source << ":\n";
        for(int i = 0; i < V; i++) {
            if(dist[i] == INT_MAX) {
                cout << "  Vertex " << i << ": INF\n";
            } else {
                cout << "  Vertex " << i << ": " << dist[i] << "\n";
            }
        }
    }
};

class CompetitiveProgrammingToolkit {
private:
    TemplateGenerator templateGen;
    TestCaseGenerator testGen;
    OutputComparator comparator;
    PerformanceAnalyzer analyzer;
    GraphUtils graphUtils;
    
    void showMainMenu() {
        Utils::clearScreen();
        Utils::printHeader("COMPETITIVE PROGRAMMING TOOLKIT");
        cout << "\n";
        cout << "  ╔══════════════════════════════════════════════╗\n";
        cout << "  ║  1. Generate Code Template                   ║\n";
        cout << "  ║  2. Generate Test Case                       ║\n";
        cout << "  ║  3. Compare Outputs                          ║\n";
        cout << "  ║  4. Analyze Performance                      ║\n";
        cout << "  ║  5. Graph Utilities                          ║\n";
        cout << "  ║  6. Exit                                     ║\n";
        cout << "  ╚══════════════════════════════════════════════╝\n";
        cout << "\n  Enter your choice: ";
    }
    
    void showTemplateMenu() {
        Utils::clearScreen();
        Utils::printHeader("Generate Code Template");
        templateGen.listTemplates();
        cout << "\n  Enter template name (or 'back' to return): ";
        
        string templateName;
        cin >> templateName;
        
        if(templateName != "back") {
            templateGen.generateTemplate(templateName);
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
    
    void showTestCaseMenu() {
        Utils::clearScreen();
        Utils::printHeader("Generate Test Case");
        cout << "\n  ╔══════════════════════════════════════════════╗\n";
        cout << "    ║  1. Array Test Case                          ║\n";
        cout << "    ║  2. Graph Test Case                          ║\n";
        cout << "    ║  3. String Test Case                         ║\n";
        cout << "    ║  4. Matrix Test Case                         ║\n";
        cout << "    ║  5. Custom Input                             ║\n";
        cout << "    ║  6. Back to Main Menu                        ║\n";
        cout << "    ╚══════════════════════════════════════════════╝\n";
        cout << "\n  Enter your choice: ";
    }
    
    void showCompareMenu() {
        Utils::clearScreen();
        Utils::printHeader("Compare Outputs");
        cout << "\n  ╔══════════════════════════════════════════════╗\n";
        cout << "    ║  1. Compare Two Output Files                ║\n";
        cout << "    ║  2. Compare Brute vs Optimized              ║\n";
        cout << "    ║  3. Back to Main Menu                       ║\n";
        cout << "    ╚══════════════════════════════════════════════╝\n";
        cout << "\n  Enter your choice: ";
    }
    
    void showGraphMenu() {
        Utils::clearScreen();
        Utils::printHeader("Graph Utilities");
        cout << "\n  ╔══════════════════════════════════════════════╗\n";
        cout << "  ║  1. Connectivity Check (DSU)                ║\n";
        cout << "  ║  2. Bridge Detection (Tarjan's)             ║\n";
        cout << "  ║  3. Shortest Path (Dijkstra)                ║\n";
        cout << "  ║  4. Back to Main Menu                       ║\n";
        cout << "  ╚══════════════════════════════════════════════╝\n";
        cout << "\n  Enter your choice: ";
    }
    
public:
    void run() {
        int choice;
        do {
            showMainMenu();
            cin >> choice;
            
            switch(choice) {
                case 1: {
                    showTemplateMenu();
                    break;
                }
                case 2: {
                    int testChoice;
                    do {
                        showTestCaseMenu();
                        cin >> testChoice;
                        switch(testChoice) {
                            case 1:
                                testGen.generateArrayTest();
                                break;
                            case 2:
                                testGen.generateGraphTest();
                                break;
                            case 3:
                                testGen.generateStringTest();
                                break;
                            case 4:
                                testGen.generateMatrixTest();
                                break;
                            case 5:
                                testGen.generateCustomTest();
                                break;
                        }
                        if(testChoice != 6 && testChoice >= 1 && testChoice <= 5) {
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                        }
                    } while(testChoice != 6);
                    break;
                }
                case 3: {
                    int compareChoice;
                    do {
                        showCompareMenu();
                        cin >> compareChoice;
                        if(compareChoice == 1) {
                            string file1, file2;
                            cout << "Enter first file name: ";
                            cin >> file1;
                            cout << "Enter second file name: ";
                            cin >> file2;
                            comparator.compareOutputs(file1, file2);
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                        } else if(compareChoice == 2) {
                            string brute, opt;
                            cout << "Enter brute-force output file: ";
                            cin >> brute;
                            cout << "Enter optimized output file: ";
                            cin >> opt;
                            comparator.compareWithBruteForce(brute, opt);
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                        }
                    } while(compareChoice != 3);
                    break;
                }
                case 4: {
                    string executable, inputFile;
                    cout << "Enter executable name: ";
                    cin >> executable;
                    cout << "Enter input file name: ";
                    cin >> inputFile;
                    analyzer.measureExecutionTime(executable, inputFile);
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 5: {
                    int graphChoice;
                    do {
                        showGraphMenu();
                        cin >> graphChoice;
                        switch(graphChoice) {
                            case 1:
                                graphUtils.checkConnectivity();
                                break;
                            case 2:
                                graphUtils.findBridges();
                                break;
                            case 3:
                                graphUtils.shortestPathDemo();
                                break;
                        }
                        if(graphChoice != 4 && graphChoice >= 1 && graphChoice <= 3) {
                            cout << "\nPress Enter to continue...";
                            cin.ignore();
                            cin.get();
                        }
                    } while(graphChoice != 4);
                    break;
                }
                case 6:
                    Utils::printHeader("Thank you for using CP Toolkit!");
                    cout << "\n  Happy Coding!\n\n";
                    break;
                default:
                    cout << "\nInvalid choice! Press Enter to continue...";
                    cin.ignore();
                    cin.get();
            }
        } while(choice != 6);
    }
};

int main() {
    cout << "\033[2J\033[1;1H";
    
    CompetitiveProgrammingToolkit toolkit;
    toolkit.run();
    
    return 0;
}