/* Pack_test.cpp
 * 
 * Unit tests for Card
 *
 */

#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <iostream>
using namespace std;

int main() {

  ////////////////////////////////////////
  // Pack_init() unit tests
  Pack pack;
  Pack_init(&pack, "pack.in");

  Card nine_spades = {NINE, SPADES};
  Card first_card = *(pack.next);
  assert(Card_compare(&first_card, &nine_spades) == 0);

  Card ace_diamonds = {ACE, DIAMONDS};
  Card last_card = *(pack.cards + PACK_SIZE - 1);
  assert(Card_compare(&last_card, &ace_diamonds) == 0);


  ////////////////////////////////////////
  // Pack_print() unit tests (unchecked)
  Pack_print(&pack);


  ////////////////////////////////////////
  // Pack_deal_one() unit tests
  Card c = Pack_deal_one(&pack);
  assert( Card_compare(&c, &nine_spades) == 0 );
  assert(Card_compare(&first_card, &nine_spades) == 0);

  Card ten_spades = {TEN, SPADES};
  c = Pack_deal_one(&pack);
  assert( Card_compare(&c, &ten_spades) == 0 );


  ////////////////////////////////////////
  // Pack_reset() unit tests
  Pack_reset(&pack);
  assert(Card_compare(&first_card, &nine_spades) == 0);
  

  ////////////////////////////////////////
  // Pack_shuffle() unit tests
  Pack_shuffle(&pack);

  Card queen_spades = {QUEEN, SPADES};
  first_card = *(pack.next);
  assert(Card_compare(&first_card, &queen_spades) == 0);

  Card jack_spades = {JACK, SPADES};
  last_card = *(pack.cards + PACK_SIZE - 1);
  assert(Card_compare(&last_card, &jack_spades) == 0);


  // if we got to the end without calling an assert(), the tests passed
  cout << "Pack_test PASS" << endl;

  return 0;
}
