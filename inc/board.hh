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
    bool* available_moves;
public:
    Board(int p_size, int p_win, char p_max, char p_min, char p_empty);
    Board(const Board& to_copy);
    ~Board();

    void display();
    void make_move(int i, int j, bool maximizer);
    void clear_move(int i, int j);
    bool is_move_available(int i, int j);
    bool is_full();
    void display_available_moves();

    // Winning
    bool horizontal_win(bool maximizer);
    bool vertical_win(bool maximizer);
    bool diagonal_win(bool maximizer);
    bool x_won(bool maximizer);
    bool top2bot_diagonal_win(bool maximizer);
    bool bot2top_diagonal_win(bool maximizer);
    bool game_over();

    // Getters
    int get_size() const;
    int get_win_num() const;
    char get_max_sym() const;
    char get_min_sym() const;
    char get_empty_sym() const;

    // Setters
    void set_fields(std::string tab);

    // Overloading
    const char & operator() (int row, int column);
    char operator() (int row, int column) const; 
};

#endif  // BOARD_HH
