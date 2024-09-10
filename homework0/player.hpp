// player.hpp
// Elliott Lewandowski
// September 5, 2024
//
// For CS311 Homework 0
// Header for class Player

#ifndef FILE_PLAYER_HPP_INCLUDED
#define FILE_PLAYER_HPP_INCLUDED

#include <string>

class Player {

    private:
//****** Player: Member Variables ******
        std::string m_real_name;
        std::string m_username;
        int m_games_played;

    public:
//****** Player: Constructors ******
        Player() 
            : m_real_name("UNKNOWN"),
              m_username("UNKNOWN"),
              m_games_played(0)
        {
            // Space left inentionally blank
        }

        Player(const std::string & real_name, 
               const std::string & username, 
               const int & games_played)
            : m_real_name(real_name),
              m_username(username),
              m_games_played(games_played)
        {
             // Space left inentionally blank
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

        void setRealName(const std::string & new_name)
        {
            m_real_name = new_name;
        }

        void setUsername(const std::string & new_name)
        {
            m_username = new_name;
        }

        void setGames(const int & new_games)
        {   
            if (new_games >= 0)
            {
                m_games_played = new_games;
            }
        }

//****** Player: Member Functions ******
        bool inactive() const
        {
            bool activity = !(m_games_played > 0);
            return activity;
        }

        std::string toString() const
        {
            std::string out = m_real_name +
                + " (" + m_username + "): "
                + std::to_string(m_games_played);

            return out;
        }

//****** Player: Member Operator Overrides ******
        Player & operator++()
        {
            ++m_games_played;
            return *this;
        }

        Player operator++([[maybe_unused]] int dummy)
        {
            Player save = *this;
            ++(*this);
            return save;
        }

        Player & operator--()
        {
            if (m_games_played > 0) 
                --m_games_played;
            return *this;

        }

        Player operator--([[maybe_unused]] int dummy)
        {
            Player save = *this;
            --(*this);
            return save;
        }


}; // End of class player

//****** Player: Global Operator Overrides ******
std::ostream & operator<<(std::ostream & out, const Player & player);
bool operator==(const Player & lhs, const Player & rhs);
bool operator!=(const Player & lhs, const Player & rhs);


#endif // #ifndef FILE_PLAYER_HPP_INCLUDED
