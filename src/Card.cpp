#include "StdAfx.h"
#include "Poker.h"
#include "PokerMagic.h"

namespace Poker {

  Card::Card( Suit suit, Rank rank )
  {
    mData = Magic::gPrimes[rank] | ( rank << 8 ) | suit | ( 1 << ( 16 + rank ) );
  }

  const CardData Card::getData() const throw()
  {
    return mData;
  }

  const Suit Card::getSuit() const
  {
    if ( mData & suitClubs )
      return suitClubs;
    else if ( mData & suitDiamonds )
      return suitDiamonds;
    else if ( mData & suitHearts )
      return suitHearts;
    else
      return suitSpades;
  }

  const Rank Card::getRank() const
  {
    Rank r = (Rank)( ( mData >> 8 ) & 0xF );
    return r;
  }

}