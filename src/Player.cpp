#include "StdAfx.h"
#include "Poker.h"
#include "PokerMagic.h"

namespace Poker {

  void Player::addCard( Card& card )
  {
    mCards.push_back( card );
  }

  void Player::clearCards()
  {
    mCards.clear();
  }

  const CardVector& Player::getCards() const throw()
  {
    return mCards;
  }

  const wstring& Player::getName() const throw()
  {
    return mName;
  }

}