# Tested shortest paths

This document contains the shortest path tests that were successfully executed.

## Small dataset - `dataTest.csv`

| Test ID   | Source | Destination | Number of nodes | Path | Distance units | Dijkstra | Bidirectional |
| --------- | ------ | ----------- | --------------- | ---- | -------------- | -------- | ------------- |
| AL_018_01 |        |             |                 |      |                |          |               |

## Large dataset - `USA-roads.csv`

| Test ID   | Source    | Destination | Number of nodes | Path to the result                             |
| --------- | --------- | ----------- | --------------- | ---------------------------------------------- |
| AL_019_01 | 1         | 2           | 2               | [AL_019_01](./testing/testingResuts/AL_019_01) |
| AL_019_02 | 1         | 17,902,846  | 3,610           | [AL_019_02](./testing/testingResuts/AL_019_02) |
| AL_019_04 | 1         | 22,377,087  | 2,230           | [AL_019_04](./testing/testingResuts/AL_019_04) |
| AL_019_03 | 1         | 22,382,040  | 10,192          | [AL_019_03](./testing/testingResuts/AL_019_03) |
| AL_019_04 | 7         | 12,345,678  | 2,230           | [AL_019_04](./testing/testingResuts/AL_019_04) |
| AL_019_05 | 100       | 200         | 38              | [AL_019_05](./testing/testingResuts/AL_019_05) |
| AL_019_06 | 300       | 400         | 35              | [AL_019_06](./testing/testingResuts/AL_019_06) |
| AL_019_07 | 500       | 700         | 38              | [AL_019_07](./testing/testingResuts/AL_019_07) |
| AL_019_08 | 1,234     | 5,678       | 610             | [AL_019_08](./testing/testingResuts/AL_019_08) |
| AL_019_09 | 534,968   | 5,342,161   | 1,892           | [AL_019_09](./testing/testingResuts/AL_019_09) |
| AL_019_09 | 1,534,968 | 742,900     | 1,892           | [AL_019_09](./testing/testingResuts/AL_019_09) |
| AL_019_10 | 9,876,234 | 23,359,056  | 2,017           | [AL_019_10](./testing/testingResuts/AL_019_10) |
| AL_019_11 | 9,489,093 | 22,377,086  | 13,322          | [AL_019_11](./testing/testingResuts/AL_019_11) |
| AL_019_12 | 9,489,093 | 22,377,087  | 13,323          | [AL_019_12](./testing/testingResuts/AL_019_12) |
| AL_019_13 | 9,489,093 | 22,377,088  | 13,323          | [AL_019_13](./testing/testingResuts/AL_019_13) |

## Algorithm comparison 

|               | V.1 | V.2 | V.3 | V.4 |
| ------------- | --- | --- | --- | --- |
| **AL_019_1**  |     |     |     |     |
| **AL_019_2**  |     |     |     |     |
| **AL_019_3**  |     |     |     |     |
| **AL_019_4**  |     |     |     |     |
| **AL_019_5**  |     |     |     |     |
| **AL_019_6**  |     |     |     |     |
| **AL_019_7**  |     |     |     |     |
| **AL_019_8**  |     |     |     |     |
| **AL_019_9**  |     |     |     |     |
| **AL_019_10** |     |     |     |     |
| **AL_019_11** |     |     |     |     |
| **AL_019_12** |     |     |     |     |
| **AL_019_13** |     |     |     |     |
| **AL_019_14** |     |     |     |     |
| **AL_019_15** |     |     |     |     |
| **AL_019_16** |     |     |     |     |
| **AL_019_17** |     |     |     |     |
| **AL_019_18** |     |     |     |     |
| **AL_019_19** |     |     |     |     |
| **AL_019_20** |     |     |     |     |
| **AL_019_21** |     |     |     |     |
| **AL_019_22** |     |     |     |     |
| **AL_019_23** |     |     |     |     |
| **AL_019_24** |     |     |     |     |
| **AL_019_25** |     |     |     |     |
| **AL_019_26** |     |     |     |     |
| **AL_019_27** |     |     |     |     |
| **AL_019_28** |     |     |     |     |
| **AL_019_29** |     |     |     |     |
| **AL_019_30** |     |     |     |     |
| **AL_019_31** |     |     |     |     |
| **AL_019_32** |     |     |     |     |
| **AL_019_33** |     |     |     |     |
| **AL_019_34** |     |     |     |     |
| **AL_019_35** |     |     |     |     |
| **AL_019_36** |     |     |     |     |
| **AL_019_37** |     |     |     |     |
| **AL_019_38** |     |     |     |     |
| **AL_019_39** |     |     |     |     |
| **AL_019_40** |     |     |     |     |
| **AL_019_41** |     |     |     |     |
| **AL_019_42** |     |     |     |     |
| **AL_019_43** |     |     |     |     |
| **AL_019_44** |     |     |     |     |
| **AL_019_45** |     |     |     |     |
| **AL_019_46** |     |     |     |     |
| **AL_019_47** |     |     |     |     |
| **AL_019_48** |     |     |     |     |
| **AL_019_49** |     |     |     |     |
| **AL_019_50** |     |     |     |     |
| **AL_019_51** |     |     |     |     |
| **AL_019_52** |     |     |     |     |
| **AL_019_53** |     |     |     |     |
| **AL_019_54** |     |     |     |     |
| **AL_019_55** |     |     |     |     |
| **AL_019_56** |     |     |     |     |
| **AL_019_57** |     |     |     |     |
| **AL_019_58** |     |     |     |     |
| **AL_019_59** |     |     |     |     |
| **AL_019_60** |     |     |     |     |
| **AL_019_61** |     |     |     |     |
| **AL_019_62** |     |     |     |     |
| **AL_019_63** |     |     |     |     |
| **AL_019_64** |     |     |     |     |
| **AL_019_65** |     |     |     |     |
| **AL_019_66** |     |     |     |     |
| **AL_019_67** |     |     |     |     |
| **AL_019_68** |     |     |     |     |
| **AL_019_69** |     |     |     |     |
| **AL_019_70** |     |     |     |     |
| **AL_019_71** |     |     |     |     |
| **AL_019_72** |     |     |     |     |
| **AL_019_73** |     |     |     |     |
| **AL_019_74** |     |     |     |     |
| **AL_019_75** |     |     |     |     |
| **AL_019_76** |     |     |     |     |
| **AL_019_77** |     |     |     |     |
| **AL_019_78** |     |     |     |     |
| **AL_019_79** |     |     |     |     |
| **AL_019_80** |     |     |     |     |
| **AL_019_81** |     |     |     |     |
| **AL_019_82** |     |     |     |     |
| **AL_019_83** |     |     |     |     |
| **AL_019_84** |     |     |     |     |
| **AL_019_85** |     |     |     |     |
| **AL_019_86** |     |     |     |     |
| **AL_019_87** |     |     |     |     |
| **AL_019_88** |     |     |     |     |
| **AL_019_89** |     |     |     |     |
| **AL_019_90** |     |     |     |     |
| **AL_019_91** |     |     |     |     |
| **AL_019_92** |     |     |     |     |
| **AL_019_93** |     |     |     |     |
| **AL_019_94** |     |     |     |     |
| **AL_019_95** |     |     |     |     |
| **AL_019_96** |     |     |     |     |
| **AL_019_97** |     |     |     |     |
| **AL_019_98** |     |     |     |     |
| **AL_019_99** |     |     |     |     |


| Test ID   | Source   | Destination | Number of nodes | Path to the result                             |
| --------- | -------- | ----------- | --------------- | ---------------------------------------------- |
| AL_019_1  | 3862144  | 2922307     |                 | [AL_019_1](./testing/testingResuts/AL_019_1)   |
| AL_019_2  | 316267   | 2102000     |                 | [AL_019_2](./testing/testingResuts/AL_019_2)   |
| AL_019_3  | 11989425 | 6871131     |                 | [AL_019_3](./testing/testingResuts/AL_019_3)   |
| AL_019_4  | 7880831  | 15253774    |                 | [AL_019_4](./testing/testingResuts/AL_019_4)   |
| AL_019_5  | 9659791  | 21198756    |                 | [AL_019_5](./testing/testingResuts/AL_019_5)   |
| AL_019_6  | 22946272 | 23645473    |                 | [AL_019_6](./testing/testingResuts/AL_019_6)   |
| AL_019_7  | 21782090 | 17687089    |                 | [AL_019_7](./testing/testingResuts/AL_019_7)   |
| AL_019_8  | 20021588 | 21516898    |                 | [AL_019_8](./testing/testingResuts/AL_019_8)   |
| AL_019_9  | 18875939 | 22787429    |                 | [AL_019_9](./testing/testingResuts/AL_019_9)   |
| AL_019_10 | 1433447  | 15338377    |                 | [AL_019_10](./testing/testingResuts/AL_019_10) |
| AL_019_11 | 10926287 | 21401238    |                 | [AL_019_11](./testing/testingResuts/AL_019_11) |
| AL_019_12 | 22390609 | 9521447     |                 | [AL_019_12](./testing/testingResuts/AL_019_12) |
| AL_019_13 | 12528074 | 8973549     |                 | [AL_019_13](./testing/testingResuts/AL_019_13) |
| AL_019_14 | 20307366 | 6652914     |                 | [AL_019_14](./testing/testingResuts/AL_019_14) |
| AL_019_15 | 21406120 | 20776228    |                 | [AL_019_15](./testing/testingResuts/AL_019_15) |
| AL_019_16 | 8432523  | 12081787    |                 | [AL_019_16](./testing/testingResuts/AL_019_16) |
| AL_019_17 | 21373935 | 3731424     |                 | [AL_019_17](./testing/testingResuts/AL_019_17) |
| AL_019_18 | 5249730  | 10894388    |                 | [AL_019_18](./testing/testingResuts/AL_019_18) |
| AL_019_19 | 10891244 | 20680598    |                 | [AL_019_19](./testing/testingResuts/AL_019_19) |
| AL_019_20 | 11159794 | 15498221    |                 | [AL_019_20](./testing/testingResuts/AL_019_20) |
| AL_019_21 | 1540927  | 7384123     |                 | [AL_019_21](./testing/testingResuts/AL_019_21) |
| AL_019_22 | 4522505  | 23335105    |                 | [AL_019_22](./testing/testingResuts/AL_019_22) |
| AL_019_23 | 15999528 | 81415       |                 | [AL_019_23](./testing/testingResuts/AL_019_23) |
| AL_019_24 | 16542561 | 12696876    |                 | [AL_019_24](./testing/testingResuts/AL_019_24) |
| AL_019_25 | 8863403  | 3256964     |                 | [AL_019_25](./testing/testingResuts/AL_019_25) |
| AL_019_26 | 11394016 | 6279996     |                 | [AL_019_26](./testing/testingResuts/AL_019_26) |
| AL_019_27 | 20236164 | 16303161    |                 | [AL_019_27](./testing/testingResuts/AL_019_27) |
| AL_019_28 | 15839644 | 20772445    |                 | [AL_019_28](./testing/testingResuts/AL_019_28) |
| AL_019_29 | 21222114 | 8594239     |                 | [AL_019_29](./testing/testingResuts/AL_019_29) |
| AL_019_30 | 7908121  | 3972964     |                 | [AL_019_30](./testing/testingResuts/AL_019_30) |
| AL_019_31 | 13362683 | 20871241    |                 | [AL_019_31](./testing/testingResuts/AL_019_31) |
| AL_019_32 | 3666846  | 15072774    |                 | [AL_019_32](./testing/testingResuts/AL_019_32) |
| AL_019_33 | 22280044 | 13440207    |                 | [AL_019_33](./testing/testingResuts/AL_019_33) |
| AL_019_34 | 2001728  | 3716772     |                 | [AL_019_34](./testing/testingResuts/AL_019_34) |
| AL_019_35 | 20552508 | 9152489     |                 | [AL_019_35](./testing/testingResuts/AL_019_35) |
| AL_019_36 | 13062809 | 12121914    |                 | [AL_019_36](./testing/testingResuts/AL_019_36) |
| AL_019_37 | 1645894  | 22695007    |                 | [AL_019_37](./testing/testingResuts/AL_019_37) |
| AL_019_38 | 2983023  | 21182236    |                 | [AL_019_38](./testing/testingResuts/AL_019_38) |
| AL_019_39 | 20853545 | 13943313    |                 | [AL_019_39](./testing/testingResuts/AL_019_39) |
| AL_019_40 | 23627627 | 14720885    |                 | [AL_019_40](./testing/testingResuts/AL_019_40) |
| AL_019_41 | 843310   | 10191372    |                 | [AL_019_41](./testing/testingResuts/AL_019_41) |
| AL_019_42 | 16829583 | 15507718    |                 | [AL_019_42](./testing/testingResuts/AL_019_42) |
| AL_019_43 | 22289802 | 22308023    |                 | [AL_019_43](./testing/testingResuts/AL_019_43) |
| AL_019_44 | 20604315 | 5395877     |                 | [AL_019_44](./testing/testingResuts/AL_019_44) |
| AL_019_45 | 12850605 | 13167657    |                 | [AL_019_45](./testing/testingResuts/AL_019_45) |
| AL_019_46 | 21726018 | 9253531     |                 | [AL_019_46](./testing/testingResuts/AL_019_46) |
| AL_019_47 | 13878670 | 17518491    |                 | [AL_019_47](./testing/testingResuts/AL_019_47) |
| AL_019_48 | 11280887 | 22776767    |                 | [AL_019_48](./testing/testingResuts/AL_019_48) |
| AL_019_49 | 17351207 | 8461429     |                 | [AL_019_49](./testing/testingResuts/AL_019_49) |
| AL_019_50 | 959185   | 19131675    |                 | [AL_019_50](./testing/testingResuts/AL_019_50) |
| AL_019_51 | 23758688 | 19364745    |                 | [AL_019_51](./testing/testingResuts/AL_019_51) |
| AL_019_52 | 19209720 | 41315       |                 | [AL_019_52](./testing/testingResuts/AL_019_52) |
| AL_019_53 | 23591925 | 20066785    |                 | [AL_019_53](./testing/testingResuts/AL_019_53) |
| AL_019_54 | 4853124  | 11319961    |                 | [AL_019_54](./testing/testingResuts/AL_019_54) |
| AL_019_55 | 4289408  | 13154473    |                 | [AL_019_55](./testing/testingResuts/AL_019_55) |
| AL_019_56 | 11765562 | 7722400     |                 | [AL_019_56](./testing/testingResuts/AL_019_56) |
| AL_019_57 | 15169930 | 14539041    |                 | [AL_019_57](./testing/testingResuts/AL_019_57) |
| AL_019_58 | 6103830  | 7452780     |                 | [AL_019_58](./testing/testingResuts/AL_019_58) |
| AL_019_59 | 20257598 | 4806359     |                 | [AL_019_59](./testing/testingResuts/AL_019_59) |
| AL_019_60 | 18074223 | 10400340    |                 | [AL_019_60](./testing/testingResuts/AL_019_60) |
| AL_019_61 | 1954656  | 10135070    |                 | [AL_019_61](./testing/testingResuts/AL_019_61) |
| AL_019_62 | 9691672  | 14106526    |                 | [AL_019_62](./testing/testingResuts/AL_019_62) |
| AL_019_63 | 16320661 | 21513858    |                 | [AL_019_63](./testing/testingResuts/AL_019_63) |
| AL_019_64 | 21537088 | 16595993    |                 | [AL_019_64](./testing/testingResuts/AL_019_64) |
| AL_019_65 | 4935914  | 7822407     |                 | [AL_019_65](./testing/testingResuts/AL_019_65) |
| AL_019_66 | 15777653 | 18166684    |                 | [AL_019_66](./testing/testingResuts/AL_019_66) |
| AL_019_67 | 16916593 | 16394522    |                 | [AL_019_67](./testing/testingResuts/AL_019_67) |
| AL_019_68 | 14476784 | 6797495     |                 | [AL_019_68](./testing/testingResuts/AL_019_68) |
| AL_019_69 | 3203194  | 10861238    |                 | [AL_019_69](./testing/testingResuts/AL_019_69) |
| AL_019_70 | 17082225 | 21326114    |                 | [AL_019_70](./testing/testingResuts/AL_019_70) |
| AL_019_71 | 439061   | 10485402    |                 | [AL_019_71](./testing/testingResuts/AL_019_71) |
| AL_019_72 | 13245274 | 6119488     |                 | [AL_019_72](./testing/testingResuts/AL_019_72) |
| AL_019_73 | 14249382 | 1732816     |                 | [AL_019_73](./testing/testingResuts/AL_019_73) |
| AL_019_74 | 4181965  | 5722190     |                 | [AL_019_74](./testing/testingResuts/AL_019_74) |
| AL_019_75 | 21886861 | 5623280     |                 | [AL_019_75](./testing/testingResuts/AL_019_75) |
| AL_019_76 | 11725639 | 7844265     |                 | [AL_019_76](./testing/testingResuts/AL_019_76) |
| AL_019_77 | 6375233  | 3338811     |                 | [AL_019_77](./testing/testingResuts/AL_019_77) |
| AL_019_78 | 17294323 | 18136599    |                 | [AL_019_78](./testing/testingResuts/AL_019_78) |
| AL_019_79 | 16573153 | 7189885     |                 | [AL_019_79](./testing/testingResuts/AL_019_79) |
| AL_019_80 | 6146634  | 21796348    |                 | [AL_019_80](./testing/testingResuts/AL_019_80) |
| AL_019_81 | 9963656  | 3846101     |                 | [AL_019_81](./testing/testingResuts/AL_019_81) |
| AL_019_82 | 15288001 | 19399304    |                 | [AL_019_82](./testing/testingResuts/AL_019_82) |
| AL_019_83 | 16140660 | 9914049     |                 | [AL_019_83](./testing/testingResuts/AL_019_83) |
| AL_019_84 | 10597240 | 5279405     |                 | [AL_019_84](./testing/testingResuts/AL_019_84) |
| AL_019_85 | 1        | 2           | 2               | [AL_019_85](./testing/testingResuts/AL_019_85) |
| AL_019_86 | 1        | 17902,846   | 3610            | [AL_019_86](./testing/testingResuts/AL_019_86) |
| AL_019_87 | 1        | 22377087    | 2230            | [AL_019_87](./testing/testingResuts/AL_019_87) |
| AL_019_88 | 1        | 22382040    | 10192           | [AL_019_88](./testing/testingResuts/AL_019_88) |
| AL_019_89 | 7        | 12345678    | 2230            | [AL_019_89](./testing/testingResuts/AL_019_89) |
| AL_019_90 | 100      | 200         | 38              | [AL_019_90](./testing/testingResuts/AL_019_90) |
| AL_019_91 | 300      | 400         | 35              | [AL_019_91](./testing/testingResuts/AL_019_91) |
| AL_019_92 | 500      | 700         | 38              | [AL_019_92](./testing/testingResuts/AL_019_92) |
| AL_019_93 | 1234     | 5678        | 610             | [AL_019_93](./testing/testingResuts/AL_019_93) |
| AL_019_94 | 534968   | 5342161     | 1892            | [AL_019_94](./testing/testingResuts/AL_019_94) |
| AL_019_95 | 1534968  | 742900      | 1892            | [AL_019_95](./testing/testingResuts/AL_019_95) |
| AL_019_96 | 9876234  | 23359056    | 2017            | [AL_019_96](./testing/testingResuts/AL_019_96) |
| AL_019_97 | 9489093  | 22377086    | 13322           | [AL_019_97](./testing/testingResuts/AL_019_97) |
| AL_019_98 | 9489093  | 22377087    | 13323           | [AL_019_98](./testing/testingResuts/AL_019_98) |
| AL_019_99 | 9489093  | 22377088    | 13323           | [AL_019_99](./testing/testingResuts/AL_019_99) |
