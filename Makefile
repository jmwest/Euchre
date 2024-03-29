# Build Card unit test executable
Card_test : Card_test.cpp Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 Card_test.cpp Card.cpp -o Card_test

# Build Pack unit test executable
Pack_test : Pack_test.cpp Pack.cpp Pack.h Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 Pack_test.cpp Pack.cpp Card.cpp -o Pack_test

# Build Player unit test executable
Player_test : Player_test.cpp Player.cpp Player.h Pack.cpp Pack.h Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 Player_test.cpp Player.cpp Pack.cpp Card.cpp -o Player_test

# Build the top-level euchre executable
euchre : euchre.cpp Game.cpp Game.h Player.cpp Player.h Pack.cpp Pack.h Card.cpp Card.h
	g++ -pedantic -Wall -Werror -O1 euchre.cpp Game.cpp Player.cpp Pack.cpp Card.cpp -o euchre

# Run regression test and check output
test : Card_test Pack_test Player_test euchre
	./Card_test > Card_test.out
	./Pack_test > Pack_test.out
	./Player_test > Player_test.out
	./euchre pack.in noshuffle 1 Alice Bob Cathy Drew > euchre_test00.out
	diff -q euchre_test00.out euchre_test00.out.correct
	./euchre pack.in shuffle 10 Alice Bob Cathy Drew > euchre_test01.out
	diff -q euchre_test01.out euchre_test01.out.correct

test2: euchre
	./euchre pack2.in noshuffle 10 Rick Steve Mack Horace > euchre_test10.out
	./euchre pack2.in shuffle 30 Rick Steve Mack Horace > euchre_test11.out
	./euchre pack3.in noshuffle 10 Rachel Anna John Damian > euchre_test20.out
	diff -q euchre_test20.out euchre_test20.out.anna
	./euchre pack3.in shuffle 99 Rachel Anna John Damian > euchre_test21.out
	diff -q euchre_test21.out euchre_test21.out.anna
	./euchre pack4.in noshuffle 25 Thor Hulk Widow Spidey > euchre_test04.out.john
	diff -q euchre_test04.out euchre_test04.out.john
	./euchre pack4.in shuffle 25 Thor Hulk Widow Spidey > euchre_test05.out.john

# type "make clean" to delete executables and temporary files
clean :
	rm -vf *.out euchre Card_test Pack_test Player_test
