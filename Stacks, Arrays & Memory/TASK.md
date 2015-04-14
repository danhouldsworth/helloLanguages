# TASK

1. Make an RPNsolver that takes a string of numbers and operators(+,-,/,*) and outputs the result.
2. Extend the supported numbers to include floats, 'pi' and 'e'
3. Extend the supported operators with 'sum', 'ln', '^', 'sin', 'cos', '!'
4. Add stack operators 'push', 'pop', '<>', '>>', '<<'


## Solve these examples to verify equivalence: (Answer === Algerbraic === RPN)

        1 === 5 / ( 4 + ( 3 - ( 2 * 1 ) ) )                             === '5 4 3 2 1 * - + /'
        2 === ( ( Sin( Pi / 4 ) ) ^ 2 ) * 4                             === 'pi 4 / sin 2 ^ 4 *'
        3 === 1 / ( ( Sin( Pi / Fact(3) ) / Cos( Pi / Fact(3) ) ) ^ 2 ) === '1 pi 3 ! / push sin <> cos / 2 ^ /'


## More complex (and slightly contrived) examples to demonstrate the advantages of RPN over Algebraic calculators:

### Calculate the sum of the first 4 terms of : (2n-1)*Sin((2n-1)*Pi/2) + 2n*Cos(2n*Pi/2) [n=1,2,3,4]

Algerbraic:
        (2*1-1)*Sin((2*1-1)*pi/2)+(2*1)*Cos((2*1)*pi/2)+(2*2-1)*Sin((2*2-1)*pi/2)+(2*2)*Cos((2*2)*pi/2)+(3*2-1)*Sin((3*2-1)*pi/2)+(3*2)*Cos((3*2)*pi/2)+(4*2-1)*Sin((4*2-1)*pi/2)+(4*2)*Cos((4*2)*pi/2)
vs

RPN:
        1 1 - push pi 1 1 + / push << 1 + push >> * sin << push >> * <> >> + << push << 1 + push >> * cos << push >> * <> >> + << push << 1 + push >> * sin << push >> * <> >> + << push << 1 + push >> * cos << push >> * <> >> + << << pop pop

Maybe that doesn't seem an improvement, what if we try and calculate for more terms, say [n=1..8]

Algerbraic:
        (2*1-1)*Sin((2*1-1)*pi/2)+(2*1)*Cos((2*1)*pi/2)+(2*2-1)*Sin((2*2-1)*pi/2)+(2*2)*Cos((2*2)*pi/2)+(2*3-1)*Sin((2*3-1)*pi/2)+(2*3)*Cos((2*3)*pi/2)+(2*4-1)*Sin((2*4-1)*pi/2)+(2*4)*Cos((2*4)*pi/2)+(2*5-1)*Sin((2*5-1)*pi/2)+(2*5)*Cos((2*5)*pi/2)+(2*6-1)*Sin((2*6-1)*pi/2)+(2*6)*Cos((2*6)*pi/2)+(2*7-1)*Sin((2*7-1)*pi/2)+(2*7)*Cos((2*7)*pi/2)+(2*8-1)*Sin((2*8-1)*pi/2)+(2*8)*Cos((2*8)*pi/2)

vs

RPN (line breaks included to highlight the repeating pattern):
        1 1 - push pi 1 1 + /
        push << 1 + push >> * sin << push >> * <> >> + <<
        push << 1 + push >> * cos << push >> * <> >> + <<
        push << 1 + push >> * sin << push >> * <> >> + <<
        push << 1 + push >> * cos << push >> * <> >> + <<
        push << 1 + push >> * sin << push >> * <> >> + <<
        push << 1 + push >> * cos << push >> * <> >> + <<
        push << 1 + push >> * sin << push >> * <> >> + <<
        push << 1 + push >> * cos << push >> * <> >> + <<
        push << 1 + push >> * sin << push >> * <> >> + <<
        push << 1 + push >> * cos << push >> * <> >> + <<
        push << 1 + push >> * sin << push >> * <> >> + <<
        push << 1 + push >> * cos << push >> * <> >> + <<
        << pop pop

It's easy to see that the RPN method could quickly be extended to an arbitrary number of terms, whereas it is increasinly likely the user will make a mistake keeping track of the algerbraic terms.
Note : impressively the RPN method made use of only two constants : ```PI``` and ```1``` !!!


### Calculate PI to 4dps using the [continued fraction](http://en.wikipedia.org/wiki/Pi#Continued_fractions) :

Eg.
        Pi = 4 / term(n) [ where term(n) = (2n-1) + (n^2) / term(n+1) ]

Algerbraic:
        3.1416 === 4 / (1 + (1^2) / (3 + (2^2) / (5 + (3^2) / (7 + (4^2) / (9 + (5^2) / (11 + (6^2) / 13))))))

vs

RPN:
        3.1416 === 4 1 1 2 ^ 3 2 2 ^ 5 3 2 ^ 7 4 2 ^ 9 5 2 ^ 11 6 2 ^ 13 / + / + / + / + / + / + /

Again, maybe doesn't seem like an improvement at first, but if we wanted to go further to 6dps (3.141592)...?

Algerbraic:
        4 / (1 + (1^2) / (3 + (2^2) / (5 + (3^2) / (7 + (4^2) / (9 + (5^2) / (11 + (6^2) / (13 + (7^2) / (15 + (8^2) / (17 + (9^2) / 19)))))))))
vs

RPN (line breaks included to highlight the repeating pattern):
        1 1 4
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << << push 2 + >> <> push 1 + >> 2 ^
        << pop << /
        + / + / + / + / + / + / + / + / + /

Again, it's easy to see that the RPN method could arbitrarily extended more quickly and reliabely than algerbraic calculations.

