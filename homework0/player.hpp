
#ifndef FILE_PLAYER_HPP_INCLUDED
#define FILE_PLAYER_HPP_INCLUDED

#include <string>

class Player {
//****** Player: Member Variables ******
    private:
        std::string m_real_name;
        std::string m_username;
        uint m_games_played;

    public:
//****** Player: Constructors ******
        Player() 
        {
            setRealName("UNKOWN");
            setUsername("UNKOWN");
            setGames(0);
        }

        Player(std::string real_name, std::string username, int games_played)
        {
            setRealName(real_name);
            setUsername(username);
            setGames(games_played);
        }

//****** Player: Getters and Setters ******
        std::string getRealName() const
        {
            return m_real_name;
        }

        std::string getUsername() const
        {
            return m_username;
        }

        int getGames() const
        {
            return m_games_played;
        }

        void setRealName(std::string new_name)
        {
            m_real_name = new_name;
        }

        void setUsername(std::string new_name)
        {
            m_username = new_name;
        }

        void setGames(int new_games)
        {
            m_games_played = new_games;
        }

//****** Player: Member Functions ******
        bool inactive() const
        {
            bool activity = (m_games_played > 0);
            return activity;
        }

        std::string toString() const
        {

        }

//****** Player: Member Operator Overrides ******
        Player & operator++()
        {
            
        }

        Player operator++([[maybe_unused]] int dummy)
        {

        }

        Player & operator--()
        {

        }

        Player operator--([[maybe_unused]] int dummy)
        {

        }


}; // End of class player

//****** Player: Global Operator Overrides ******
std::ostream & operator<<(std::ostream & out, const Player & player);
bool operator==(const Player & lhs, const Player & rhs);
bool operator!=(const Player & lhs, const Player & rhs);


#endif // #ifndef FILE_PLAYER_HPP_INCLUDED
