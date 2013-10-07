#ifndef CARD_H
#define CARD_H
/* Card.h
 *
 * Represents a single playing card
 *
 * by Andrew DeOrio
 * awdeorio@umich.edu
 * 2013-09-06
 */


////////////////////////////////////////////////////////////////////////////////
// Suit

// The suits in a deck of cards
enum Suit { SPADES, HEARTS, CLUBS, DIAMONDS };

//MODIFIES stdout
//EFFECTS  prints Suit to standard output, for example "Spades" or "Hearts"
void Suit_print(Suit suit);

//EFFECTS returns the next suit, or suit of the same color
Suit Suit_next(Suit suit);


////////////////////////////////////////////////////////////////////////////////
// Rank

// The ranks in a deck of cards
enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
            JACK, QUEEN, KING, ACE };


////////////////////////////////////////////////////////////////////////////////
// Card

// A card has a rank and a suit, for example "Two of Spades"
struct Card {
  Rank rank;
  Suit suit;
};

//MODIFIES card_ptr
//EFFECTS Initializes Card pointed to by card_ptr to specified card
void Card_init(Card *card_ptr, Rank rank, Suit suit);

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"  
//MODIFIES card_ptr
//EFFECTS Initializes Card pointed to by card_ptr to specified card
void Card_init(Card *card_ptr, const char* rank, const char* suit);

//MODIFIES stdout
//EFFECTS  Prints Card to standard output, for example "Two of Spades"
void Card_print(const Card *card_ptr);

//EFFECTS Returns true if card_ptr is a face card (Jack, Queen, King or Ace)
bool Card_is_face(const Card *card_ptr);

//EFFECTS Returns true if card_ptr is the Jack of the trump suit
bool Card_is_right_bower(const Card *card_ptr, Suit trump);

//EFFECTS Returns true if card_ptr is the Jack of the next suit
bool Card_is_left_bower(const Card *card_ptr, Suit trump);

//EFFECTS Returns true if the card_ptr is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card_is_trump(const Card *card_ptr, Suit trump);

//EFFECTS Returns zero if suits are equal.  A value greater than zero indicates
//  that the Suit of a has a higher value than s.  A value less than zero 
//  indicates that the Suit s has a higher value than a.
//  Hint: the left bower's suit is the *trump* suit
int Card_compare_suit(const Card *a, Suit s, Suit trump);

//EFFECTS Returns zero if cards are equal.  A value greater than zero indicates
//  that a has a higher value than b.  A value less than zero indicates that b
//  has a higher value than a.  Does not consider trump.
int Card_compare(const Card *a, const Card *b);

//EFFECTS Returns zero if cards are equal.  A value greater than zero indicates
//  that a has a higher value than b.  A value less than zero indicates that b
//  has a higher value than a.  Uses trump to determine order, as described in 
//  the spec.
int Card_compare(const Card *a, const Card *b, Suit trump);

//EFFECTS Returns zero if cards are equal.  A value greater than zero indicates
//  that a has a higher value than b.  A value less than zero indicates that b
//  has a higher value than a.  Uses both trump and the suit led to determine
//  order, as described in the spec.
int Card_compare(const Card *a, const Card *b, Suit trump, Suit led);

#endif
