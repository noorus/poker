#include "StdAfx.h"
#include "Poker.h"

using namespace Poker;

wstring cardToString( const Card& card )
{
  wstring s;
  Rank rank = card.getRank();
  switch ( rank )
  {
    case rankDeuce: s = L"2"; break;
    case rankTrey: s = L"3"; break;
    case rankFour: s = L"4"; break;
    case rankFive: s = L"5"; break;
    case rankSix: s = L"6"; break;
    case rankSeven: s = L"7"; break;
    case rankEight: s = L"8"; break;
    case rankNine: s = L"9"; break;
    case rankTen: s = L"10"; break;
    case rankJack: s = L"J"; break;
    case rankQueen: s = L"Q"; break;
    case rankKing: s = L"K"; break;
    case rankAce: s = L"A"; break;
  }
  Suit suit = card.getSuit();
  switch ( suit )
  {
    case suitHearts: s.append( L"h" ); break;
    case suitDiamonds: s.append( L"d" ); break;
    case suitClubs: s.append( L"c" ); break;
    case suitSpades: s.append( L"s" ); break;
  }
  return s;
}

void printDeck( Deck& deck )
{
  for ( CardVector::const_iterator it = deck.getCards().begin(); it != deck.getCards().end(); ++it )
  {
    wprintf_s( L"- %s\r\n", cardToString( (*it) ).c_str() );
  }
  wprintf_s( L"Total of %d cards.\r\n", deck.getCards().size() );
}

void printPlayer( Player& player )
{
  wstring cardstr;
  for ( const Card card : player.getCards() )
    cardstr.append( cardToString( card ) + L" " );
  wprintf_s( L"- %s has: %s\r\n", player.getName().c_str(), cardstr.c_str() );
}

void printPlayerHand( Player* player, HandRank rank )
{
  wstring rankstr;
  switch ( rank )
  {
    case handHigh: rankstr = L"nothing"; break;
    case handPair: rankstr = L"a Pair"; break;
    case handTwoPair: rankstr = L"Two Pairs"; break;
    case handThreeOfAKind: rankstr = L"Three of a Kind"; break;
    case handStraight: rankstr = L"a Straight"; break;
    case handFlush: rankstr = L"a Flush"; break;
    case handFullHouse: rankstr = L"a Full House!"; break;
    case handFourOfAKind: rankstr = L"Four of a Kind!"; break;
    case handStraightFlush: rankstr = L"a Straight Flush!"; break;
  }
  wprintf_s( L"- %s has %s\r\n", player->getName().c_str(), rankstr.c_str() );
}

void printTable( CardVector& cards )
{
  wstring hand;
  for ( Card card : cards )
    hand.append( cardToString( card ) + L" " );
  wprintf_s( L"- The table has: %s\r\n", hand.c_str() );
}

static wstring gNameTable[5] = {
  L"Player A", L"Player B", L"Player C", L"Player D", L"Player E"
};

int wmain( int argc, WCHAR* argv[] )
{
  srand( GetTickCount() );

  wprintf_s( L"Dealing cards!\r\n" );

  CardVector table;

  PlayerList players;

  for ( int i = 0; i < 5; i++ )
  {
    Player* player = new Player( gNameTable[i] );
    players.push_back( player );
  }

  Deck deck;

  deck.initialize();
  deck.shuffle();
  deck.burn();

  for ( int i = 0; i < 2; i++ )
    for ( Player* player : players )
      player->addCard( deck.deal() );

  deck.burn();

  for ( int i = 0; i < 3; i++ )
    table.push_back( deck.deal() );

  deck.burn();
  table.push_back( deck.deal() );
  deck.burn();
  table.push_back( deck.deal() );

  for ( Player* player : players )
    printPlayer( *player );

  printTable( table );

  wprintf_s( L"Valuation:\r\n" );

  Evaluator evaluator;

  short highest = 9999;
  Player* highestPlr = nullptr;

  for ( Player* player : players )
  {
    CardData arr[7] = { 0 };
    arr[0] = player->getCards()[0].getData();
    arr[1] = player->getCards()[1].getData();
    arr[2] = table[0].getData();
    arr[3] = table[1].getData();
    arr[4] = table[2].getData();
    arr[5] = table[3].getData();
    arr[6] = table[4].getData();
    HandValue value = evaluator.evaluate7( arr );
    if ( value < highest )
    {
      highest = value;
      highestPlr = player;
    }
    printPlayerHand( player, evaluator.rankHand( value ) );
  }

  if ( highestPlr )
    wprintf_s( L"%s wins.\r\n", highestPlr->getName().c_str() );

  for ( Player* player : players )
    delete player;

  return 0;
}