# TASK

1. Make an RPNsolver that takes a string of numbers and operators(+,-,/,*) and outputs the result.
2. Extend the supported numbers to include floats, 'pi' and 'e'
3. Extend the supported operators with 'sum', 'ln', '^', 'sin', 'cos', '!'
4. Add stack operators 'push', '<>', '>>', '<<'


Solve these examples to verify equivalence: (Answer === Algerbraic === RPN)

        1 === 5 / ( 4 + ( 3 - ( 2 * 1 ) ) )                             === '5 4 3 2 1 * - + /'
        2 === ( ( Sin( Pi / 4 ) ) ^ 2 ) * 4                             === 'pi 4 / sin 2 ^ 4 *'
        3 === 1 / ( ( Sin( Pi / Fact(3) ) / Cos( Pi / Fact(3) ) ) ^ 2 ) === '1 pi 3 ! / push sin <> cos / 2 ^ /'
        0 ===
        ( Sin( 1 * Pi / ( 1 + 1 ) ) + ( 1 + 1 ) * Cos( ( 1 + 1 ) * Pi / ( 1 + 1 ) ) + ( 1 + 1 + 1 ) * Sin( ( 1 + 1 + 1 ) * Pi / ( 1 + 1 ) ) + ( 1 + 1 + 1 + 1 ) * Cos( ( 1 + 1 + 1 + 1 ) * Pi / ( 1 + 1 ) ) )
        'pi 1 1 + push >> / push push push sin << <> >> push >> * cos << push >> * << 1 + push >> >> * sin << * >> 1 1 1 1 + + + push >> * cos << * sum'

Admittedly, the fourth one is somewhat contrived....
index / sum / pi2
0 0 pi 1 1 + /                          : 0 0 pi/2
push << 1 + push >>                     : 1 0 pi/2 pi/2 1
* sin << push >> *                      : 1 0 pi/2 1
<> >> + <<                              : 1 1 Pi/2

push << 1 + push >>                     : 2 1 pi/2 pi/2 2
* cos << push >> *                      : 2 1 pi/2 -2
<> >> + <<                              : 2 -1 pi/2

push << 1 + push >>                     : 2 1 pi/2 pi/2 2
* sin << push >> *                      : 2 1 pi/2 -2
<> >> + <<                              : 2 -1 pi/2

push << 1 + push >>                     : 2 1 pi/2 pi/2 2
* cos << push >> *                      : 2 1 pi/2 -2
<> >> + <<                              : 2 -1 pi/2

0 0 pi 1 1 + /
push << 1 + push >> * sin << push >> * <> >> + <<
push << 1 + push >> * cos << push >> * <> >> + <<
push << 1 + push >> * sin << push >> * <> >> + <<
push << 1 + push >> * cos << push >> * <> >> + <<

0 0 pi 1 1 + / push << 1 + push >> * sin << push >> * <> >> + << push << 1 + push >> * cos << push >> * <> >> + << push << 1 + push >> * sin << push >> * <> >> + << push << 1 + push >> * cos << push >> * <> >> + <<
