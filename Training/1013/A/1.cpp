#include <cstdint>
#include <cstdio>

const int64_t MOD = 1e9 + 7;

const int N = 1e3 + 10;
int64_t n, m, ans, f[N];

int64_t pow(int64_t a, int exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}

int64_t sum(int64_t x) {
    int64_t ret = f[x / 1000000];
    for (int64_t i = x / 1000000 * 1000000 + 1; i <= x; i++)
        (ret += 2 * i % MOD * pow((i + 1) * (i + 2) % MOD, MOD - 2)) %= MOD;
    return ret;
}

int main() {
    static int T;
    scanf("%d", &T);
f[1] = 903236543;
f[2] = 588865143;
f[3] = 654159909;
f[4] = 901453314;
f[5] = 645734439;
f[6] = 476817918;
f[7] = 460012107;
f[8] = 576975110;
f[9] = 592375965;
f[10] = 562966670;
f[11] = 603740807;
f[12] = 615265315;
f[13] = 150845912;
f[14] = 676154985;
f[15] = 610860889;
f[16] = 137063400;
f[17] = 682677709;
f[18] = 388573406;
f[19] = 39477457;
f[20] = 196991375;
f[21] = 314495345;
f[22] = 734476918;
f[23] = 294800575;
f[24] = 41231131;
f[25] = 341059229;
f[26] = 825258218;
f[27] = 179797242;
f[28] = 4096118;
f[29] = 535254783;
f[30] = 557917842;
f[31] = 627901149;
f[32] = 83858366;
f[33] = 944867928;
f[34] = 4505002;
f[35] = 270336417;
f[36] = 56185636;
f[37] = 751627108;
f[38] = 631447365;
f[39] = 475776305;
f[40] = 87402497;
f[41] = 937552852;
f[42] = 367710969;
f[43] = 123204678;
f[44] = 521285535;
f[45] = 194873822;
f[46] = 516650730;
f[47] = 73802993;
f[48] = 738017052;
f[49] = 955166422;
f[50] = 904768555;
f[51] = 115020902;
f[52] = 839269605;
f[53] = 205320764;
f[54] = 577177086;
f[55] = 239014487;
f[56] = 753693367;
f[57] = 320386208;
f[58] = 3917161;
f[59] = 18742978;
f[60] = 921247297;
f[61] = 367569830;
f[62] = 719145967;
f[63] = 322410978;
f[64] = 481321788;
f[65] = 60453812;
f[66] = 486459067;
f[67] = 53622204;
f[68] = 316970295;
f[69] = 123538323;
f[70] = 475707948;
f[71] = 206144738;
f[72] = 907686296;
f[73] = 686185536;
f[74] = 415645873;
f[75] = 658643546;
f[76] = 549958731;
f[77] = 918246632;
f[78] = 743970206;
f[79] = 436863622;
f[80] = 666407559;
f[81] = 812263577;
f[82] = 887432143;
f[83] = 742623309;
f[84] = 451605629;
f[85] = 310510913;
f[86] = 820431559;
f[87] = 805243415;
f[88] = 61996706;
f[89] = 744306140;
f[90] = 377623444;
f[91] = 121198569;
f[92] = 699252362;
f[93] = 605777689;
f[94] = 492344560;
f[95] = 331153144;
f[96] = 154447643;
f[97] = 921161760;
f[98] = 727227414;
f[99] = 798436342;
f[100] = 616087699;
f[101] = 22766957;
f[102] = 220736546;
f[103] = 596770897;
f[104] = 984382164;
f[105] = 712701233;
f[106] = 676026149;
f[107] = 451151351;
f[108] = 169196597;
f[109] = 236866281;
f[110] = 700149351;
f[111] = 207494416;
f[112] = 363980561;
f[113] = 211172066;
f[114] = 519798075;
f[115] = 871855163;
f[116] = 212452302;
f[117] = 421274381;
f[118] = 78455423;
f[119] = 214419872;
f[120] = 696875255;
f[121] = 8596782;
f[122] = 39718193;
f[123] = 435562437;
f[124] = 814994344;
f[125] = 681997679;
f[126] = 540386361;
f[127] = 23157643;
f[128] = 717294118;
f[129] = 595124657;
f[130] = 53744750;
f[131] = 774398511;
f[132] = 187665855;
f[133] = 778160874;
f[134] = 771672795;
f[135] = 910952130;
f[136] = 345600489;
f[137] = 905617496;
f[138] = 486340371;
f[139] = 94154713;
f[140] = 244213587;
f[141] = 603174650;
f[142] = 53515988;
f[143] = 47388295;
f[144] = 840817407;
f[145] = 88113612;
f[146] = 754260324;
f[147] = 709057613;
f[148] = 584680976;
f[149] = 614981459;
f[150] = 980931358;
f[151] = 522829584;
f[152] = 391262785;
f[153] = 931257379;
f[154] = 171180466;
f[155] = 354231279;
f[156] = 366186526;
f[157] = 69191213;
f[158] = 716710094;
f[159] = 874729668;
f[160] = 620778988;
f[161] = 112969895;
f[162] = 345337726;
f[163] = 376907372;
f[164] = 262990559;
f[165] = 435113734;
f[166] = 42378890;
f[167] = 453774289;
f[168] = 495699353;
f[169] = 650513805;
f[170] = 467326170;
f[171] = 627503109;
f[172] = 324633566;
f[173] = 312085259;
f[174] = 25106152;
f[175] = 507521331;
f[176] = 950418321;
f[177] = 200374266;
f[178] = 416408898;
f[179] = 907922931;
f[180] = 204319525;
f[181] = 788746400;
f[182] = 810685227;
f[183] = 877053177;
f[184] = 690866748;
f[185] = 885153561;
f[186] = 352854431;
f[187] = 250416564;
f[188] = 635262324;
f[189] = 806455496;
f[190] = 419113417;
f[191] = 870429236;
f[192] = 503179402;
f[193] = 525709384;
f[194] = 621606901;
f[195] = 468402254;
f[196] = 741458052;
f[197] = 823646852;
f[198] = 856351849;
f[199] = 332160472;
f[200] = 60671180;
f[201] = 529943098;
f[202] = 472529848;
f[203] = 920829348;
f[204] = 774261058;
f[205] = 453601519;
f[206] = 241462155;
f[207] = 281538643;
f[208] = 787252152;
f[209] = 184336972;
f[210] = 484282770;
f[211] = 223985179;
f[212] = 382722557;
f[213] = 934657775;
f[214] = 217284148;
f[215] = 897536668;
f[216] = 180379158;
f[217] = 480662180;
f[218] = 543478745;
f[219] = 664905600;
f[220] = 442309834;
f[221] = 13806372;
f[222] = 130147394;
f[223] = 415080820;
f[224] = 377396184;
f[225] = 774507543;
f[226] = 399313407;
f[227] = 376619188;
f[228] = 714320165;
f[229] = 210378589;
f[230] = 382594474;
f[231] = 224470661;
f[232] = 348301594;
f[233] = 723250751;
f[234] = 148206586;
f[235] = 205494397;
f[236] = 596902356;
f[237] = 19876893;
f[238] = 461255659;
f[239] = 876792565;
f[240] = 542772749;
f[241] = 661224596;
f[242] = 598805350;
f[243] = 794327247;
f[244] = 639434939;
f[245] = 444464631;
f[246] = 111209676;
f[247] = 791160182;
f[248] = 35358930;
f[249] = 737929446;
f[250] = 60948891;
f[251] = 445391702;
f[252] = 613382269;
f[253] = 152273533;
f[254] = 19024523;
f[255] = 487043459;
f[256] = 177306178;
f[257] = 275487177;
f[258] = 943047348;
f[259] = 691601562;
f[260] = 280397020;
f[261] = 333161206;
f[262] = 518653754;
f[263] = 332475208;
f[264] = 666118202;
f[265] = 397765901;
f[266] = 761039835;
f[267] = 156184216;
f[268] = 777802769;
f[269] = 968576736;
f[270] = 560191244;
f[271] = 176371547;
f[272] = 967387048;
f[273] = 891986203;
f[274] = 419406480;
f[275] = 134796834;
f[276] = 60198036;
f[277] = 619677403;
f[278] = 550611814;
f[279] = 231468555;
f[280] = 739201661;
f[281] = 854959279;
f[282] = 517748971;
f[283] = 883817160;
f[284] = 989220986;
f[285] = 450993819;
f[286] = 435747299;
f[287] = 820187422;
f[288] = 381278577;
f[289] = 597757824;
f[290] = 500132262;
f[291] = 965057542;
f[292] = 900223244;
f[293] = 343161727;
f[294] = 435442009;
f[295] = 302793494;
f[296] = 909189411;
f[297] = 824131657;
f[298] = 273335691;
f[299] = 752693913;
f[300] = 712761532;
f[301] = 970151552;
f[302] = 151510469;
f[303] = 568781549;
f[304] = 125718514;
f[305] = 417171995;
f[306] = 108065688;
f[307] = 459779228;
f[308] = 967919304;
f[309] = 322970456;
f[310] = 242893110;
f[311] = 825431203;
f[312] = 496528683;
f[313] = 902400200;
f[314] = 490971547;
f[315] = 532632128;
f[316] = 377564538;
f[317] = 921671827;
f[318] = 534963858;
f[319] = 403057893;
f[320] = 102438679;
f[321] = 787938936;
f[322] = 895255779;
f[323] = 62824811;
f[324] = 952745895;
f[325] = 957333659;
f[326] = 485186995;
f[327] = 861859385;
f[328] = 798305238;
f[329] = 515040525;
f[330] = 550547969;
f[331] = 764806341;
f[332] = 322131341;
f[333] = 363974146;
f[334] = 233226381;
f[335] = 518300292;
f[336] = 912549452;
f[337] = 35291406;
f[338] = 963834179;
f[339] = 861508021;
f[340] = 411014869;
f[341] = 966475528;
f[342] = 607239488;
f[343] = 419196824;
f[344] = 396580213;
f[345] = 886942428;
f[346] = 789044831;
f[347] = 904072681;
f[348] = 221770557;
f[349] = 32602534;
f[350] = 672358836;
f[351] = 163705661;
f[352] = 641303981;
f[353] = 129713898;
f[354] = 643520438;
f[355] = 704139884;
f[356] = 1973947;
f[357] = 298108120;
f[358] = 323602319;
f[359] = 289487311;
f[360] = 445259621;
f[361] = 516522624;
f[362] = 930427131;
f[363] = 692058263;
f[364] = 185906511;
f[365] = 465700779;
f[366] = 341643404;
f[367] = 963256010;
f[368] = 260036251;
f[369] = 889669295;
f[370] = 825692879;
f[371] = 408749021;
f[372] = 422094276;
f[373] = 708294185;
f[374] = 174196231;
f[375] = 636088237;
f[376] = 143153449;
f[377] = 261750438;
f[378] = 324710938;
f[379] = 685881132;
f[380] = 851977846;
f[381] = 145177522;
f[382] = 780277797;
f[383] = 912317944;
f[384] = 466734724;
f[385] = 295642906;
f[386] = 596092168;
f[387] = 999356444;
f[388] = 830177875;
f[389] = 315773412;
f[390] = 678779835;
f[391] = 130877255;
f[392] = 998561531;
f[393] = 260997001;
f[394] = 561734998;
f[395] = 683249616;
f[396] = 130144187;
f[397] = 738860148;
f[398] = 679111812;
f[399] = 900435043;
f[400] = 533066735;
f[401] = 869097766;
f[402] = 397794821;
f[403] = 110106058;
f[404] = 57710589;
f[405] = 387054238;
f[406] = 937621133;
f[407] = 886670375;
f[408] = 51615394;
f[409] = 762774683;
f[410] = 530275456;
f[411] = 716397850;
f[412] = 511774228;
f[413] = 628051234;
f[414] = 672998959;
f[415] = 890362949;
f[416] = 564438401;
f[417] = 564752349;
f[418] = 605534725;
f[419] = 38004526;
f[420] = 58937949;
f[421] = 243877006;
f[422] = 297222536;
f[423] = 257187492;
f[424] = 132745896;
f[425] = 411968583;
f[426] = 602084893;
f[427] = 121737783;
f[428] = 399377416;
f[429] = 890836865;
f[430] = 449278276;
f[431] = 22159142;
f[432] = 521877815;
f[433] = 820885746;
f[434] = 445970639;
f[435] = 487731831;
f[436] = 825721506;
f[437] = 382090947;
f[438] = 406278696;
f[439] = 673075042;
f[440] = 638877427;
f[441] = 167981794;
f[442] = 917741050;
f[443] = 255768419;
f[444] = 220549370;
f[445] = 524732683;
f[446] = 887729315;
f[447] = 387628397;
f[448] = 342946721;
f[449] = 949909075;
f[450] = 800491036;
f[451] = 917797081;
f[452] = 77992927;
f[453] = 382824352;
f[454] = 49002348;
f[455] = 473543371;
f[456] = 56505351;
f[457] = 734588059;
f[458] = 661704972;
f[459] = 807713849;
f[460] = 190692124;
f[461] = 715007953;
f[462] = 742918509;
f[463] = 586860180;
f[464] = 349046697;
f[465] = 888320061;
f[466] = 308061734;
f[467] = 905796092;
f[468] = 167545631;
f[469] = 398762773;
f[470] = 430633713;
f[471] = 696035101;
f[472] = 296465961;
f[473] = 422906101;
f[474] = 178998425;
f[475] = 582718078;
f[476] = 500627437;
f[477] = 55038711;
f[478] = 747416633;
f[479] = 750617148;
f[480] = 262183610;
f[481] = 794410228;
f[482] = 826966379;
f[483] = 656529738;
f[484] = 163360603;
f[485] = 43025411;
f[486] = 414727126;
f[487] = 954782639;
f[488] = 389262780;
f[489] = 369452171;
f[490] = 556138952;
f[491] = 842197125;
f[492] = 504613496;
f[493] = 717248298;
f[494] = 852360504;
f[495] = 817489339;
f[496] = 145878950;
f[497] = 829283202;
f[498] = 826679354;
f[499] = 419792103;
f[500] = 707299256;
f[501] = 262870813;
f[502] = 450716347;
f[503] = 562289275;
f[504] = 8439074;
f[505] = 532267465;
f[506] = 173142509;
f[507] = 321110474;
f[508] = 934247374;
f[509] = 406462618;
f[510] = 323111480;
f[511] = 269304565;
f[512] = 109478183;
f[513] = 359770454;
f[514] = 375380967;
f[515] = 65203721;
f[516] = 745588241;
f[517] = 583153611;
f[518] = 834936034;
f[519] = 907968191;
f[520] = 728328199;
f[521] = 191466432;
f[522] = 315518024;
f[523] = 198760953;
f[524] = 252185895;
f[525] = 507584149;
f[526] = 383658324;
f[527] = 921347850;
f[528] = 381383103;
f[529] = 503553169;
f[530] = 50400630;
f[531] = 878264485;
f[532] = 862892410;
f[533] = 651119014;
f[534] = 616908333;
f[535] = 587617276;
f[536] = 414783266;
f[537] = 505538127;
f[538] = 435937250;
f[539] = 645260224;
f[540] = 446807405;
f[541] = 975515556;
f[542] = 12843815;
f[543] = 673273275;
f[544] = 613025386;
f[545] = 386010471;
f[546] = 79188435;
f[547] = 574010340;
f[548] = 955975372;
f[549] = 838168971;
f[550] = 285157274;
f[551] = 848174000;
f[552] = 547555562;
f[553] = 682533414;
f[554] = 574602103;
f[555] = 662465082;
f[556] = 562658516;
f[557] = 993414904;
f[558] = 942730645;
f[559] = 530364431;
f[560] = 72250992;
f[561] = 648063730;
f[562] = 691344548;
f[563] = 526429436;
f[564] = 7432002;
f[565] = 53155663;
f[566] = 343726081;
f[567] = 330635573;
f[568] = 334267462;
f[569] = 352592552;
f[570] = 353481564;
f[571] = 336595132;
f[572] = 632897633;
f[573] = 729115630;
f[574] = 427130746;
f[575] = 654249723;
f[576] = 709911219;
f[577] = 574266355;
f[578] = 726146978;
f[579] = 57095061;
f[580] = 196627195;
f[581] = 595176077;
f[582] = 142820343;
f[583] = 241595104;
f[584] = 728788505;
f[585] = 709280540;
f[586] = 767532144;
f[587] = 810722226;
f[588] = 238545648;
f[589] = 975883092;
f[590] = 62510878;
f[591] = 225897724;
f[592] = 646780940;
f[593] = 769318559;
f[594] = 750871167;
f[595] = 863859062;
f[596] = 492360627;
f[597] = 409137809;
f[598] = 602543803;
f[599] = 593360914;
f[600] = 517915233;
f[601] = 752288954;
f[602] = 279205041;
f[603] = 222096754;
f[604] = 950845892;
f[605] = 997122851;
f[606] = 342757687;
f[607] = 870818110;
f[608] = 207039224;
f[609] = 138462489;
f[610] = 959168720;
f[611] = 785834256;
f[612] = 469120578;
f[613] = 85734748;
f[614] = 781060148;
f[615] = 65420214;
f[616] = 46626389;
f[617] = 182452418;
f[618] = 917278061;
f[619] = 236825097;
f[620] = 810581928;
f[621] = 365733360;
f[622] = 59229049;
f[623] = 936387337;
f[624] = 72102879;
f[625] = 934014883;
f[626] = 618500484;
f[627] = 272110638;
f[628] = 779020436;
f[629] = 229190554;
f[630] = 325055263;
f[631] = 197299261;
f[632] = 133322395;
f[633] = 94860081;
f[634] = 602846478;
f[635] = 540549384;
f[636] = 334617273;
f[637] = 7530934;
f[638] = 885177885;
f[639] = 123764688;
f[640] = 159508616;
f[641] = 551095074;
f[642] = 468804728;
f[643] = 200493216;
f[644] = 260366728;
f[645] = 870257710;
f[646] = 805298469;
f[647] = 442737135;
f[648] = 913553220;
f[649] = 727230603;
f[650] = 632817319;
f[651] = 377076541;
f[652] = 961293223;
f[653] = 938024635;
f[654] = 198501650;
f[655] = 392377211;
f[656] = 846087028;
f[657] = 27355790;
f[658] = 573257228;
f[659] = 338274106;
f[660] = 365423915;
f[661] = 462658384;
f[662] = 785281985;
f[663] = 246128973;
f[664] = 660067480;
f[665] = 824102740;
f[666] = 218346770;
f[667] = 764016889;
f[668] = 859912753;
f[669] = 507919501;
f[670] = 120853875;
f[671] = 128636484;
f[672] = 662411125;
f[673] = 708869505;
f[674] = 133286961;
f[675] = 744400935;
f[676] = 809125726;
f[677] = 714122324;
f[678] = 801924481;
f[679] = 39597090;
f[680] = 572274350;
f[681] = 578090425;
f[682] = 31459621;
f[683] = 687114845;
f[684] = 684486348;
f[685] = 617907346;
f[686] = 161942033;
f[687] = 634975836;
f[688] = 736880313;
f[689] = 432356858;
f[690] = 231568620;
f[691] = 977561337;
f[692] = 568157595;
f[693] = 629735088;
f[694] = 709199915;
f[695] = 457232173;
f[696] = 685845931;
f[697] = 699278133;
f[698] = 904635510;
f[699] = 472066093;
f[700] = 920464722;
f[701] = 71353930;
f[702] = 996822602;
f[703] = 650593276;
f[704] = 905320103;
f[705] = 375735662;
f[706] = 766874748;
f[707] = 965106917;
f[708] = 303084644;
f[709] = 926166359;
f[710] = 586032765;
f[711] = 742141881;
f[712] = 686804497;
f[713] = 240345907;
f[714] = 792988844;
f[715] = 668702414;
f[716] = 377677035;
f[717] = 783770145;
f[718] = 887250817;
f[719] = 4371189;
f[720] = 827357524;
f[721] = 415799308;
f[722] = 824589872;
f[723] = 407320806;
f[724] = 38828360;
f[725] = 948716134;
f[726] = 792369821;
f[727] = 806315698;
f[728] = 383421303;
f[729] = 842704265;
f[730] = 151810940;
f[731] = 486910945;
f[732] = 631662998;
f[733] = 107444492;
f[734] = 378949640;
f[735] = 328300424;
f[736] = 609257638;
f[737] = 751130533;
f[738] = 420571184;
f[739] = 42721747;
f[740] = 618003738;
f[741] = 770127457;
f[742] = 62312891;
f[743] = 99854918;
f[744] = 698949151;
f[745] = 271176058;
f[746] = 225129186;
f[747] = 104070385;
f[748] = 669299083;
f[749] = 726989877;
f[750] = 919068549;
f[751] = 12702651;
f[752] = 787695467;
f[753] = 148491130;
f[754] = 816031661;
f[755] = 844720940;
f[756] = 429418621;
f[757] = 71382435;
f[758] = 412824876;
f[759] = 68427927;
f[760] = 11119482;
f[761] = 908572060;
f[762] = 807620574;
f[763] = 318600797;
f[764] = 774591524;
f[765] = 998623539;
f[766] = 782621207;
f[767] = 327953378;
f[768] = 609903832;
f[769] = 226514833;
f[770] = 469418525;
f[771] = 519835843;
f[772] = 716919004;
f[773] = 22064913;
f[774] = 225679002;
f[775] = 188172523;
f[776] = 56099951;
f[777] = 517078985;
f[778] = 455377597;
f[779] = 27626247;
f[780] = 52291495;
f[781] = 910916809;
f[782] = 66434936;
f[783] = 691115109;
f[784] = 797518830;
f[785] = 829699246;
f[786] = 121824855;
f[787] = 860283927;
f[788] = 702184985;
f[789] = 114883856;
f[790] = 974487390;
f[791] = 331574339;
f[792] = 486352706;
f[793] = 318829201;
f[794] = 869351343;
f[795] = 607898933;
f[796] = 526339063;
f[797] = 564693708;
f[798] = 13836225;
f[799] = 589803307;
f[800] = 960243834;
f[801] = 428489608;
f[802] = 580314187;
f[803] = 740528118;
f[804] = 578726673;
f[805] = 844369897;
f[806] = 538776726;
f[807] = 681703639;
f[808] = 883072450;
f[809] = 485166848;
f[810] = 814281505;
f[811] = 851497338;
f[812] = 446326211;
f[813] = 234248199;
f[814] = 642064002;
f[815] = 367775789;
f[816] = 384326521;
f[817] = 932136113;
f[818] = 852903881;
f[819] = 239232218;
f[820] = 414919048;
f[821] = 752757545;
f[822] = 962295026;
f[823] = 171175435;
f[824] = 395498326;
f[825] = 306677848;
f[826] = 687008934;
f[827] = 448372565;
f[828] = 258830324;
f[829] = 665233191;
f[830] = 267544252;
f[831] = 125729298;
f[832] = 782130314;
f[833] = 332133166;
f[834] = 106706765;
f[835] = 434066330;
f[836] = 590535381;
f[837] = 637344826;
f[838] = 110667610;
f[839] = 484385764;
f[840] = 671382079;
f[841] = 491383804;
f[842] = 144322548;
f[843] = 149704934;
f[844] = 785223462;
f[845] = 764596981;
f[846] = 181789903;
f[847] = 500667221;
f[848] = 933539804;
f[849] = 901506422;
f[850] = 315723079;
f[851] = 448614528;
f[852] = 761271732;
f[853] = 413298515;
f[854] = 38920425;
f[855] = 75770712;
f[856] = 863660563;
f[857] = 407522138;
f[858] = 669229378;
f[859] = 482514690;
f[860] = 331045700;
f[861] = 954148617;
f[862] = 987003536;
f[863] = 142517029;
f[864] = 460867467;
f[865] = 722439330;
f[866] = 374228597;
f[867] = 936933217;
f[868] = 843509243;
f[869] = 276437834;
f[870] = 594283264;
f[871] = 775317120;
f[872] = 21442149;
f[873] = 325679797;
f[874] = 957779736;
f[875] = 975689;
f[876] = 336437076;
f[877] = 995796841;
f[878] = 730875812;
f[879] = 583399160;
f[880] = 440143846;
f[881] = 806599737;
f[882] = 328789967;
f[883] = 733746304;
f[884] = 306191535;
f[885] = 307386997;
f[886] = 632649368;
f[887] = 192820601;
f[888] = 286685543;
f[889] = 393795842;
f[890] = 97677038;
f[891] = 844962135;
f[892] = 886246542;
f[893] = 416637473;
f[894] = 350440590;
f[895] = 640432785;
f[896] = 506623484;
f[897] = 874015748;
f[898] = 805702735;
f[899] = 698819421;
f[900] = 202675358;
f[901] = 698781720;
f[902] = 385440338;
f[903] = 85161448;
f[904] = 5600577;
f[905] = 406968869;
f[906] = 901018647;
f[907] = 727647737;
f[908] = 855647701;
f[909] = 655173890;
f[910] = 571291271;
f[911] = 611028380;
f[912] = 439965265;
f[913] = 974383936;
f[914] = 568809039;
f[915] = 256331090;
f[916] = 360309480;
f[917] = 649401862;
f[918] = 817315215;
f[919] = 294112631;
f[920] = 893775416;
f[921] = 153936539;
f[922] = 30774137;
f[923] = 841680602;
f[924] = 289689812;
f[925] = 793007199;
f[926] = 586143061;
f[927] = 975685957;
f[928] = 523674624;
f[929] = 68171388;
f[930] = 813866819;
f[931] = 85296125;
f[932] = 405926076;
f[933] = 710587648;
f[934] = 408432888;
f[935] = 586491434;
f[936] = 982131226;
f[937] = 960638522;
f[938] = 184451211;
f[939] = 825159340;
f[940] = 909423673;
f[941] = 690612138;
f[942] = 954320869;
f[943] = 331995604;
f[944] = 756664328;
f[945] = 31480707;
f[946] = 309920912;
f[947] = 502025985;
f[948] = 324890935;
f[949] = 717496070;
f[950] = 311087975;
f[951] = 536527990;
f[952] = 484494961;
f[953] = 645957648;
f[954] = 945767020;
f[955] = 453006555;
f[956] = 76486363;
f[957] = 86740341;
f[958] = 121627183;
f[959] = 105793031;
f[960] = 111076536;
f[961] = 550744226;
f[962] = 690771909;
f[963] = 840189709;
f[964] = 929631305;
f[965] = 551173736;
f[966] = 663686523;
f[967] = 844919549;
f[968] = 374827672;
f[969] = 222464424;
f[970] = 321811713;
f[971] = 289685927;
f[972] = 224095669;
f[973] = 79765038;
f[974] = 570339190;
f[975] = 6429572;
f[976] = 524628;
f[977] = 782741013;
f[978] = 72921793;
f[979] = 460320845;
f[980] = 760858136;
f[981] = 73391565;
f[982] = 185319574;
f[983] = 507625558;
f[984] = 671059220;
f[985] = 257892979;
f[986] = 112804425;
f[987] = 760829249;
f[988] = 883842879;
f[989] = 614926711;
f[990] = 290361306;
f[991] = 785013267;
f[992] = 185518533;
f[993] = 633986771;
f[994] = 607755850;
f[995] = 303073920;
f[996] = 110593079;
f[997] = 187689696;
f[998] = 739250278;
f[999] = 405827034;
f[1000] = 366666669;
    while (T--) {
        scanf("%lld%lld", &n, &m);
        ans = (sum(n - 1) - sum(m) + MOD) % MOD;
        (ans += m * pow(m + 2, MOD - 2)) %= MOD;
        (ans *= n + 1) %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
