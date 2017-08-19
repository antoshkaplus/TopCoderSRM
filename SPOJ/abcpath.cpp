#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>
#include <set>
#include <limits>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

using Count = int;
using Index = int;
using Int = int;


struct Position {
    // operators see below
    constexpr Position() : Position(0, 0) {}
    constexpr Position(Int row, Int col) : row(row), col(col) {}
    
    //Position(Int row, Int col) : row(row), col(col) {}
    
    void set(Int row, Int col) {
        this->row = row;
        this->col = col;
    }
    
    void shift(Int row, Int col) {
        this->row += row;
        this->col += col;
    }
    
    
    
    Position& operator=(const Position& p) {
        row = p.row;
        col = p.col;
        return *this;
    }
    
    Position shifted(Int row_shift, Int col_shift) const {
        return {row + row_shift, col + col_shift};
    }
    
    struct TopLeftComparator {
        bool operator()(const Position& p_0, const Position& p_1) {
            return p_0.row < p_1.row || (p_0.row == p_1.row && p_0.col < p_1.col);
        }
    };
    
    Int row, col;
    
};   

bool operator==(const Position& p_0, const Position& p_1) {
    return p_0.row == p_1.row && p_0.col == p_1.col;
}        


template<class T>
struct Grid {
    using value_type = T;
    
    typename std::vector<T>::const_iterator begin() const {
        return grid_.begin();
    }
    typename std::vector<T>::iterator begin() {
        return grid_.begin();
    }
    typename std::vector<T>::const_iterator end() const {
        return grid_.end();
    }
    typename std::vector<T>::iterator end() {
        return grid_.end();
    }
    
    Grid() : Grid(0, 0) {}
    Grid(Count row_count, Count col_count)
    :   row_count_(row_count), 
    col_count_(col_count), 
    grid_(row_count*col_count) {}
    
    
    void resize(Count row_count, Count col_count) {
        row_count_ = row_count;
        col_count_ = col_count;
        grid_.resize(row_count*col_count);
    }
    
    void fill(const T& t) {
        std::fill(grid_.begin(), grid_.end(), t);
    }
    
    Count row_count() const { return row_count_; }
    Count col_count() const { return col_count_; }
    
    Count cell_count() const { return row_count()*col_count(); } 
    
    T& operator()(Int row, Int col) {
        return grid_[row*col_count_ + col];
    }
    
    const T& operator()(Int row, Int col) const {
        return grid_[row*col_count_ + col];
    }
    
    T& operator[](const Position& p) {
        return grid_[p.row*col_count_ + p.col];
    }
    const T& operator[](const Position& p) const {
        return grid_[p.row*col_count_ + p.col];
    }
    
    bool isInside(const Position& p) const {
        return isInside(p.row, p.col);
    }
    bool isInside(Int row, Int col) const {
        return row >= 0 && row < row_count_ && 
        col >= 0 && col < col_count_;
    }
    
    template<class Proc>
    void ForEachAround(const Position& t, Proc& proc) {
        for (auto dr = -1; dr <= 1; ++dr) {
            for (auto dc = -1; dc <= 1; ++dc) {
                auto p = t.shifted(dr, dc);
                if (isInside(p)) proc(p, t);
            }
        }
    }
    
    // proc arg: const Position&
    template<class Process> 
    void ForEachPosition(Process& proc) const {
        for (Index r = 0; r < row_count(); ++r) {
            for (Index c = 0; c < col_count(); ++c) {
                proc(Position{r, c});
            }
        }
    } 
    
private:
    
    Count row_count_, col_count_;
    std::vector<T> grid_;
};


int main(int argc, char **argv) {
    std::ios_base::sync_with_stdio(false);
    
    int test_case = 0;
    for (;;) {
        int H, W;
        cin >> H >> W;
        if (H == 0 && W == 0) {
            break;
        }
        ++test_case; 
        
        Grid<int> g(H, W);
        string s;
        for (auto i = 0; i < H; ++i) {
            cin >> s;
            for (auto j = 0; j < W; ++j) {
                g(i, j) = s[j] - 'A';
            }
        }
        
        vector<Position> vis;
        auto func = [&](const Position& p) {
            if (g[p] == 0) vis.push_back(p);
        };
        g.ForEachPosition(func);
        vector<Position> next;
        auto res = 0;
        auto func_2 = [&](const Position& p, const Position& from) {
            if (g[p] == res) {
                next.push_back(p);
            }
        };
        while (!vis.empty()) {
            ++res;
            while (!vis.empty()) {
                g.ForEachAround(vis.back(), func_2);
                vis.pop_back();
            }
            sort(next.begin(), next.end(), Position::TopLeftComparator());
            next.erase(unique(next.begin(), next.end()), next.end());
            swap(vis, next);
            next.clear();
        }
        
        cout << "Case " << test_case << ": " << res << endl;
    }
}
