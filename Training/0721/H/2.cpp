#include <cstdio>

long double a[5][5][5][5];
int ta, b, c, d;

int main() {
    freopen("school.in", "r", stdin);
    freopen("school.out", "w", stdout);
    {
        a[1][1][1][1] = 8.00000000000000000520;
        a[1][1][1][2] = 9.00000000000000000607;
        a[1][1][1][3] = 10.00000000000000000607;
        a[1][1][1][4] = 11.00000000000000000607;
        a[1][1][2][1] = 9.00000000000000000607;
        a[1][1][2][2] = 10.73000000000000000305;
        a[1][1][2][3] = 11.52166666666666667001;
        a[1][1][2][4] = 12.41472222222222222560;
        a[1][1][3][1] = 10.00000000000000000607;
        a[1][1][3][2] = 11.52166666666666667001;
        a[1][1][3][3] = 12.66541666666666667018;
        a[1][1][3][4] = 13.45118055555555555951;
        a[1][1][4][1] = 11.00000000000000000607;
        a[1][1][4][2] = 12.41472222222222222560;
        a[1][1][4][3] = 13.45118055555555555951;
        a[1][1][4][4] = 14.53260416666666667018;
        a[1][2][1][1] = 9.00000000000000000607;
        a[1][2][1][2] = 10.73000000000000000132;
        a[1][2][1][3] = 11.52166666666666666914;
        a[1][2][1][4] = 12.41472222222222222560;
        a[1][2][2][1] = 10.73000000000000000132;
        a[1][2][2][2] = 14.09656648241977583858;
        a[1][2][2][3] = 14.75728814806284866674;
        a[1][2][2][4] = 15.56674703033391906140;
        a[1][2][3][1] = 11.52166666666666666914;
        a[1][2][3][2] = 14.75728814806284866674;
        a[1][2][3][3] = 15.87229956905864543086;
        a[1][2][3][4] = 16.61764764305451252784;
        a[1][2][4][1] = 12.41472222222222222560;
        a[1][2][4][2] = 15.56674703033391906140;
        a[1][2][4][3] = 16.61764764305451252784;
        a[1][2][4][4] = 17.67245754444978256270;
        a[1][3][1][1] = 10.00000000000000000607;
        a[1][3][1][2] = 11.52166666666666667001;
        a[1][3][1][3] = 12.66541666666666667018;
        a[1][3][1][4] = 13.45118055555555555865;
        a[1][3][2][1] = 11.52166666666666666914;
        a[1][3][2][2] = 14.75728814806284866674;
        a[1][3][2][3] = 15.87229956905864543260;
        a[1][3][2][4] = 16.61764764305451252784;
        a[1][3][3][1] = 12.66541666666666667018;
        a[1][3][3][2] = 15.87229956905864543260;
        a[1][3][3][3] = 17.29680423355062655888;
        a[1][3][3][4] = 17.97177617567934655024;
        a[1][3][4][1] = 13.45118055555555555865;
        a[1][3][4][2] = 16.61764764305451252784;
        a[1][3][4][3] = 17.97177617567934655024;
        a[1][3][4][4] = 18.98807228568489216189;
        a[1][4][1][1] = 11.00000000000000000607;
        a[1][4][1][2] = 12.41472222222222222560;
        a[1][4][1][3] = 13.45118055555555555951;
        a[1][4][1][4] = 14.53260416666666666758;
        a[1][4][2][1] = 12.41472222222222222560;
        a[1][4][2][2] = 15.56674703033391906140;
        a[1][4][2][3] = 16.61764764305451252784;
        a[1][4][2][4] = 17.67245754444978256270;
        a[1][4][3][1] = 13.45118055555555555865;
        a[1][4][3][2] = 16.61764764305451252784;
        a[1][4][3][3] = 17.97177617567934655024;
        a[1][4][3][4] = 18.98807228568489216189;
        a[1][4][4][1] = 14.53260416666666666758;
        a[1][4][4][2] = 17.67245754444978256270;
        a[1][4][4][3] = 18.98807228568489216189;
        a[1][4][4][4] = 20.13949356811634535183;
        a[2][1][1][1] = 9.00000000000000000607;
        a[2][1][1][2] = 10.73000000000000000132;
        a[2][1][1][3] = 11.52166666666666666914;
        a[2][1][1][4] = 12.41472222222222222560;
        a[2][1][2][1] = 10.73000000000000000132;
        a[2][1][2][2] = 14.09656648241977583858;
        a[2][1][2][3] = 14.75728814806284866848;
        a[2][1][2][4] = 15.56674703033391906140;
        a[2][1][3][1] = 11.52166666666666666914;
        a[2][1][3][2] = 14.75728814806284866848;
        a[2][1][3][3] = 15.87229956905864543433;
        a[2][1][3][4] = 16.61764764305451252784;
        a[2][1][4][1] = 12.41472222222222222560;
        a[2][1][4][2] = 15.56674703033391906140;
        a[2][1][4][3] = 16.61764764305451252784;
        a[2][1][4][4] = 17.67245754444978256270;
        a[2][2][1][1] = 10.73000000000000000132;
        a[2][2][1][2] = 14.09656648241977583945;
        a[2][2][1][3] = 14.75728814806284866935;
        a[2][2][1][4] = 15.56674703033391906314;
        a[2][2][2][1] = 14.09656648241977583945;
        a[2][2][2][2] = 20.40446104996456359176;
        a[2][2][2][3] = 20.97778151656046369267;
        a[2][2][2][4] = 21.71982154833599551642;
        a[2][2][3][1] = 14.75728814806284866935;
        a[2][2][3][2] = 20.97778151656046369267;
        a[2][2][3][3] = 22.09024821340155368167;
        a[2][2][3][4] = 22.80128776832219966199;
        a[2][2][4][1] = 15.56674703033391906314;
        a[2][2][4][2] = 21.71982154833599551642;
        a[2][2][4][3] = 22.80128776832219966199;
        a[2][2][4][4] = 23.83194552403085876915;
        a[2][3][1][1] = 11.52166666666666666914;
        a[2][3][1][2] = 14.75728814806284866848;
        a[2][3][1][3] = 15.87229956905864543346;
        a[2][3][1][4] = 16.61764764305451252784;
        a[2][3][2][1] = 14.75728814806284866935;
        a[2][3][2][2] = 20.97778151656046369267;
        a[2][3][2][3] = 22.09024821340155367994;
        a[2][3][2][4] = 22.80128776832219966025;
        a[2][3][3][1] = 15.87229956905864543433;
        a[2][3][3][2] = 22.09024821340155367994;
        a[2][3][3][3] = 23.68354077848877839441;
        a[2][3][3][4] = 24.34010591986157966658;
        a[2][3][4][1] = 16.61764764305451252784;
        a[2][3][4][2] = 22.80128776832219966025;
        a[2][3][4][3] = 24.34010591986157966658;
        a[2][3][4][4] = 25.34221503783997697136;
        a[2][4][1][1] = 12.41472222222222222560;
        a[2][4][1][2] = 15.56674703033391906140;
        a[2][4][1][3] = 16.61764764305451252784;
        a[2][4][1][4] = 17.67245754444978255923;
        a[2][4][2][1] = 15.56674703033391906314;
        a[2][4][2][2] = 21.71982154833599551642;
        a[2][4][2][3] = 22.80128776832219966025;
        a[2][4][2][4] = 23.83194552403085876915;
        a[2][4][3][1] = 16.61764764305451252784;
        a[2][4][3][2] = 22.80128776832219966025;
        a[2][4][3][3] = 24.34010591986157966658;
        a[2][4][3][4] = 25.34221503783997697136;
        a[2][4][4][1] = 17.67245754444978256617;
        a[2][4][4][2] = 23.83194552403085877089;
        a[2][4][4][3] = 25.34221503783997697309;
        a[2][4][4][4] = 26.48779341199867730546;
        a[3][1][1][1] = 10.00000000000000000607;
        a[3][1][1][2] = 11.52166666666666667001;
        a[3][1][1][3] = 12.66541666666666667018;
        a[3][1][1][4] = 13.45118055555555556038;
        a[3][1][2][1] = 11.52166666666666666914;
        a[3][1][2][2] = 14.75728814806284866674;
        a[3][1][2][3] = 15.87229956905864543086;
        a[3][1][2][4] = 16.61764764305451252784;
        a[3][1][3][1] = 12.66541666666666667018;
        a[3][1][3][2] = 15.87229956905864543260;
        a[3][1][3][3] = 17.29680423355062655888;
        a[3][1][3][4] = 17.97177617567934654851;
        a[3][1][4][1] = 13.45118055555555556038;
        a[3][1][4][2] = 16.61764764305451252957;
        a[3][1][4][3] = 17.97177617567934654851;
        a[3][1][4][4] = 18.98807228568489216536;
        a[3][2][1][1] = 11.52166666666666666914;
        a[3][2][1][2] = 14.75728814806284866848;
        a[3][2][1][3] = 15.87229956905864543260;
        a[3][2][1][4] = 16.61764764305451252784;
        a[3][2][2][1] = 14.75728814806284866935;
        a[3][2][2][2] = 20.97778151656046369440;
        a[3][2][2][3] = 22.09024821340155367647;
        a[3][2][2][4] = 22.80128776832219965852;
        a[3][2][3][1] = 15.87229956905864543433;
        a[3][2][3][2] = 22.09024821340155367647;
        a[3][2][3][3] = 23.68354077848877839094;
        a[3][2][3][4] = 24.34010591986157966485;
        a[3][2][4][1] = 16.61764764305451252784;
        a[3][2][4][2] = 22.80128776832219965852;
        a[3][2][4][3] = 24.34010591986157966485;
        a[3][2][4][4] = 25.34221503783997697483;
        a[3][3][1][1] = 12.66541666666666667018;
        a[3][3][1][2] = 15.87229956905864543433;
        a[3][3][1][3] = 17.29680423355062655541;
        a[3][3][1][4] = 17.97177617567934654677;
        a[3][3][2][1] = 15.87229956905864543433;
        a[3][3][2][2] = 22.09024821340155367994;
        a[3][3][2][3] = 23.68354077848877839094;
        a[3][3][2][4] = 24.34010591986157966658;
        a[3][3][3][1] = 17.29680423355062655714;
        a[3][3][3][2] = 23.68354077848877839094;
        a[3][3][3][3] = 26.26618828840970113793;
        a[3][3][3][4] = 26.86610349393343595559;
        a[3][3][4][1] = 17.97177617567934655024;
        a[3][3][4][2] = 24.34010591986157966311;
        a[3][3][4][3] = 26.86610349393343595559;
        a[3][3][4][4] = 27.83760975615691663811;
        a[3][4][1][1] = 13.45118055555555556038;
        a[3][4][1][2] = 16.61764764305451252957;
        a[3][4][1][3] = 17.97177617567934654677;
        a[3][4][1][4] = 18.98807228568489216536;
        a[3][4][2][1] = 16.61764764305451252784;
        a[3][4][2][2] = 22.80128776832219966199;
        a[3][4][2][3] = 24.34010591986157966485;
        a[3][4][2][4] = 25.34221503783997697309;
        a[3][4][3][1] = 17.97177617567934655024;
        a[3][4][3][2] = 24.34010591986157966311;
        a[3][4][3][3] = 26.86610349393343595559;
        a[3][4][3][4] = 27.83760975615691663637;
        a[3][4][4][1] = 18.98807228568489216536;
        a[3][4][4][2] = 25.34221503783997698350;
        a[3][4][4][3] = 27.83760975615691663637;
        a[3][4][4][4] = 28.99854266789793416290;
        a[4][1][1][1] = 11.00000000000000000607;
        a[4][1][1][2] = 12.41472222222222222560;
        a[4][1][1][3] = 13.45118055555555555951;
        a[4][1][1][4] = 14.53260416666666666758;
        a[4][1][2][1] = 12.41472222222222222560;
        a[4][1][2][2] = 15.56674703033391906053;
        a[4][1][2][3] = 16.61764764305451252784;
        a[4][1][2][4] = 17.67245754444978256097;
        a[4][1][3][1] = 13.45118055555555555865;
        a[4][1][3][2] = 16.61764764305451252784;
        a[4][1][3][3] = 17.97177617567934655024;
        a[4][1][3][4] = 18.98807228568489216362;
        a[4][1][4][1] = 14.53260416666666666758;
        a[4][1][4][2] = 17.67245754444978256270;
        a[4][1][4][3] = 18.98807228568489216189;
        a[4][1][4][4] = 20.13949356811634535010;
        a[4][2][1][1] = 12.41472222222222222560;
        a[4][2][1][2] = 15.56674703033391906140;
        a[4][2][1][3] = 16.61764764305451252784;
        a[4][2][1][4] = 17.67245754444978256097;
        a[4][2][2][1] = 15.56674703033391906314;
        a[4][2][2][2] = 21.71982154833599551642;
        a[4][2][2][3] = 22.80128776832219966025;
        a[4][2][2][4] = 23.83194552403085876915;
        a[4][2][3][1] = 16.61764764305451252784;
        a[4][2][3][2] = 22.80128776832219966025;
        a[4][2][3][3] = 24.34010591986157966485;
        a[4][2][3][4] = 25.34221503783997696789;
        a[4][2][4][1] = 17.67245754444978256097;
        a[4][2][4][2] = 23.83194552403085876915;
        a[4][2][4][3] = 25.34221503783997697483;
        a[4][2][4][4] = 26.48779341199867730546;
        a[4][3][1][1] = 13.45118055555555556038;
        a[4][3][1][2] = 16.61764764305451252957;
        a[4][3][1][3] = 17.97177617567934654677;
        a[4][3][1][4] = 18.98807228568489216362;
        a[4][3][2][1] = 16.61764764305451252784;
        a[4][3][2][2] = 22.80128776832219966199;
        a[4][3][2][3] = 24.34010591986157966485;
        a[4][3][2][4] = 25.34221503783997697309;
        a[4][3][3][1] = 17.97177617567934655024;
        a[4][3][3][2] = 24.34010591986157966658;
        a[4][3][3][3] = 26.86610349393343595559;
        a[4][3][3][4] = 27.83760975615691663811;
        a[4][3][4][1] = 18.98807228568489216362;
        a[4][3][4][2] = 25.34221503783997697136;
        a[4][3][4][3] = 27.83760975615691663811;
        a[4][3][4][4] = 28.99854266789793416290;
        a[4][4][1][1] = 14.53260416666666666758;
        a[4][4][1][2] = 17.67245754444978256444;
        a[4][4][1][3] = 18.98807228568489216362;
        a[4][4][1][4] = 20.13949356811634535010;
        a[4][4][2][1] = 17.67245754444978256097;
        a[4][4][2][2] = 23.83194552403085876915;
        a[4][4][2][3] = 25.34221503783997697136;
        a[4][4][2][4] = 26.48779341199867730546;
        a[4][4][3][1] = 18.98807228568489216362;
        a[4][4][3][2] = 25.34221503783997697309;
        a[4][4][3][3] = 27.83760975615691663984;
        a[4][4][3][4] = 28.99854266789793416290;
        a[4][4][4][1] = 20.13949356811634535183;
        a[4][4][4][2] = 26.48779341199867730546;
        a[4][4][4][3] = 28.99854266789793416810;
        a[4][4][4][4] = 30.43968633704354634362;
    }
    scanf("%d%d%d%d", &ta, &b, &c, &d);
    printf("%.20Lf\n", a[ta][b][c][d]);
    return 0;
}