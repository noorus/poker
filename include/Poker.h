#pragma once

#include <list>
#include <vector>
#include <string>
#include <cstdint>

namespace Poker {

  using std::uint8_t;
  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;

  using std::list;
  using std::vector;
  using std::string;
  using std::wstring;

  enum Suit: uint32_t {
    suitSpades = 0x1000,
    suitHearts = 0x2000,
    suitDiamonds = 0x4000,
    suitClubs = 0x8000
  };

  enum Rank: uint32_t {
    rankDeuce = 0,
    rankTrey,
    rankFour,
    rankFive,
    rankSix,
    rankSeven,
    rankEight,
    rankNine,
    rankTen,
    rankJack,
    rankQueen,
    rankKing,
    rankAce
  };

  enum HandRank {
    handHigh = 0,
    handPair,
    handTwoPair,
    handThreeOfAKind,
    handStraight,
    handFlush,
    handFullHouse,
    handFourOfAKind,
    handStraightFlush
  };

  typedef uint32_t CardData;
  typedef uint16_t HandValue;

  class Card {
  protected:
    CardData mData;
  public:
    Card( Suit suit, Rank rank );
    const CardData getData() const throw();
    const Suit getSuit() const;
    const Rank getRank() const;
  };

  typedef vector<Card> CardVector;

  class Deck {
  protected:
    CardVector mCards;
  public:
    void initialize();
    void shuffle();
    void burn();
    Card deal();
    const CardVector& getCards() const throw();
  };

  class Player {
  protected:
    CardVector mCards;
    wstring mName;
  public:
    Player( const wstring _name ): mName( _name ) {}
    ~Player() {}
    void addCard( Card& card );
    void clearCards();
    const CardVector& getCards() const throw();
    const wstring& getName() const throw();
  };

  typedef list<Player*> PlayerList;

  class Evaluator {
  protected:
    uint32_t hash( uint32_t u );
    HandValue evaluate( CardData c1, CardData c2, CardData c3, CardData c4, CardData c5 );
  public:
    HandValue evaluate5( CardData* hand );
    HandValue evaluate7( CardData* hand );
    HandRank rankHand( HandValue value );
  };

}