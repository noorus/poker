#include "StdAfx.h"
#include "Poker.h"
#include "PokerMagic.h"

namespace Poker {

  void Deck::initialize()
  {
    mCards.clear();
    int suit = suitClubs;
    for ( int i = 0; i < 4; i++, suit >>= 1 )
    {
      for ( int j = 0; j < 13; j++ )
      {
        mCards.push_back( Card( (Suit)suit, (Rank)j ) );
      }
    }
  }

  const CardVector& Deck::getCards() const throw()
  {
    return mCards;
  }

  void Deck::shuffle()
  {
    std::random_shuffle( mCards.begin(), mCards.end() );
  }

  void Deck::burn()
  {
    mCards.pop_back();
  }

  Card Deck::deal()
  {
    Card card = mCards.back();
    mCards.pop_back();
    return card;
  }

}