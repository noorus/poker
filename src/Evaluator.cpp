#include "StdAfx.h"
#include "Poker.h"
#include "PokerMagic.h"

namespace Poker {

  // This is an implementation of Cactus Kev's evaluator,
  // http://www.suffecool.net/poker/evaluator.html
  // With the additional optimization by Paul Senzee,
  // http://www.paulsenzee.com/2006/06/some-perfect-hash.html
  // This is not the original implementation.

  uint32_t Evaluator::hash( uint32_t u )
  {
    uint32_t a, b, r;
    u += 0xe91aaa35;
    u ^= u >> 16;
    u += u << 8;
    u ^= u >> 4;
    b  = ( u >> 8 ) & 0x1ff;
    a  = ( u + ( u << 2 ) ) >> 19;
    r  = a ^ Magic::gHashAdjust[b];
    return r;
  }

  HandValue Evaluator::evaluate( CardData c1, CardData c2, CardData c3, CardData c4, CardData c5 )
  {
    CardData q = ( c1 | c2 | c3 | c4 | c5 ) >> 16;
    HandValue s;
    // check for flushes and straight flushes
    if ( c1 & c2 & c3 & c4 & c5 & 0xf000 )
      return Magic::gFlushes[q];
    // check for straights and high card hands
    if ( ( s = Magic::gUnique5[q] ) )
      return s;
    return Magic::gHashValues[hash( (c1 & 0xff) * (c2 & 0xff) * (c3 & 0xff) * (c4 & 0xff) * (c5 & 0xff) )];
  }

  HandValue Evaluator::evaluate5( CardData* hand )
  {
    CardData c1, c2, c3, c4, c5;
    c1 = *hand++;
    c2 = *hand++;
    c3 = *hand++;
    c4 = *hand++;
    c5 = *hand;
    return evaluate( c1, c2, c3, c4, c5 );
  }

  // this is a sub-optimal extension of the 5-card evaluator to 7 cards.
  // more optimal 7-card evaluators tend to require prohibitively large
  // external lookup tables, and since *extreme* performance is not a
  // requirement of mine, this is well and good enough for me.
  HandValue Evaluator::evaluate7( CardData* hand )
  {
    HandValue q, best = 9999;
    CardData i, j, subhand[5];
    for ( i = 0; i < 21; i++ )
    {
      for ( j = 0; j < 5; j++ )
        subhand[j] = hand[ Magic::gPerm7[i][j] ];
      q = evaluate5( subhand );
      if ( q < best )
        best = q;
    }
    return best;
  }

  HandRank Evaluator::rankHand( HandValue value )
  {
    if ( value > 6185 )
      return handHigh;
    if ( value > 3325 )
      return handPair;
    if ( value > 2467 )
      return handTwoPair;
    if ( value > 1609 )
      return handThreeOfAKind;
    if ( value > 1599 )
      return handStraight;
    if ( value > 322 )
      return handFlush;
    if ( value > 166 )
      return handFullHouse;
    if ( value > 10 )
      return handFourOfAKind;
    return handStraightFlush;
  }

}