#ifndef BOARD_HH
#define BOARD_HH

class Board{
private:
    int size;
    int win_num;
    char maximizer_sym;
    char minimizer_sym;
    char empty_sym;
    char** fields;
public:
    Board(int p_size, int p_win, char p_max, char p_min, char p_empty);
    ~Board();

    void display();
    void make_move(int i, int j, bool maximizer);
    bool is_move_available(int i, int j);
    bool is_full();

    // Getters
    int get_size() const;
    int get_win_num() const;
    char get_max_sym() const;
    char get_min_sym() const;
    char get_empty_sym() const;

    // Overloading
    const char & operator() (int row, int column);
    char operator() (int row, int column) const; 
};

#endif  // BOARD_HH
