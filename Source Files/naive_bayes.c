// implment your functions here
#include "..\Header Files\naive_bayes.h"
#include "..\Header Files\semen.h"
#include <stdio.h>
#include <math.h>

// Total data size; 100
#define data_size 100
// 80:20 (Training Set : Testing Set)
#define training_set 80
#define testing_set 20

//store the caculated probablities into these structs
struct probability altered;
struct probability normal;

//store error probability in the array
//double prob_error_arr[training_set][1];

float Init_Probability(float **semen)
{
    Prior_Probability();          // Init prior probability
    Prob_Season();                // Init probability for Seasons
    Prob_Childish_Disease();      // Init probability for Childish Disease
    Prob_Accident();              // Init probability for Accident / Serious Trauma
    Prob_Surgical_Intervention(); // Init probability for Surgical Intervention
    Prob_Fever();                 // Init probability for Fever
    Prob_Alcohol_Consumption();   // Init probability for Alcohol Consumption
    Prob_Smoking();               // Init probability for Smoking Habits
    Prob_Age();                   // Init probability for Age
    Prob_Sitting();               // Init probability for Sitting hours

    //print to check probability values

    //Prior Probability
    // printf("\nNormal Probability: %f, Altered Probability: %f", normal.prior_probability, altered.prior_probability);

    //Seasons
    /*
    printf("\nProb of Normal Winter, Spring, Summer, Fall: %f, %f, %f, %f", normal.winter_probability,normal.spring_probability,normal.summer_probability,normal.fall_probability);
    printf("\nProb of Alt Winter, Spring, Summer, Fall: %f, %f, %f, %f", altered.winter_probability,altered.spring_probability,altered.summer_probability,altered.fall_probability);
    */

    //Age

    //Childish Disease
    /*
    printf("\nProb of Normal Childish Disease| Yes, No: %f, %f", normal.disease_probability,normal.no_disease_probability);
    printf("\nProb of Alt Childish Disease| Yes, No: %f, %f", altered.disease_probability,altered.no_disease_probability);
    */

    //Accident / Serious Trauma
    /*
    printf("\nProb of Normal Accident/Serious Trauma| Yes, No: %f, %f", normal.trauma_probability,normal.no_trauma_probability);
    printf("\nProb of Alt Accident/Serious Trauma| Yes, No: %f, %f", altered.trauma_probability,altered.no_trauma_probability);
    */

    //Surgical Intervention
    /*
    printf("\nProb of Normal Surgical Intervention| Yes, No: %f, %f", normal.surgery_probability,normal.no_surgery_probability);
    printf("\nProb of Alt Surgical Intervention| Yes, No: %f, %f", altered.surgery_probability,altered.no_surgery_probability);
    */

    //Fever
    /*
    printf("\nProb of Normal Fever| L3, M3, No: %f, %f, %f", normal.fever_less3m_probability,normal.fever_more3m_probability,normal.no_fever_probability);
    printf("\nProb of Alt Fever| L3, M3, No: %f, %f, %f", altered.fever_less3m_probability,altered.fever_more3m_probability,altered.no_fever_probability);
    */

    //Frequency of alcohol consumption
    /*
    printf("\nProb of Normal Frequency of alcohol consumption| Several times a day, Every day, Several times a week, Once a week, Hardly ever or never: %f, %f, %f, %f, %f", normal.alcohol_several_day_probability,normal.alcohol_everyday_probability,normal.alcohol_several_week_probability,normal.alcohol_once_week_probability,normal.alcohol_hardly_probability);
    printf("\nProb of Alt Frequency of alcohol consumption| Several times a day, Every day, Several times a week, Once a week, Hardly ever or never: %f, %f, %f, %f, %f", altered.alcohol_several_day_probability,altered.alcohol_everyday_probability,altered.alcohol_several_week_probability,altered.alcohol_once_week_probability,altered.alcohol_hardly_probability);
    */

    //Smoking Habit
    /*
    printf("\nProb of Normal Smoking Habit| Never, Occasional, Daily: %f, %f, %f", normal.smoke_never_probability,normal.smoke_occasional_probability,normal.smoke_daily_probability);
    printf("\nProb of Alt Smoking Habit| Never, Occasional, Daily: %f, %f, %f", altered.smoke_never_probability,altered.smoke_occasional_probability,altered.smoke_daily_probability);
    */

    // mean + SD of age
    // printf("\nMean of age: %f", normal.age_mean);
    // printf("\nSD of age: %f", normal.age_standard_deviation);

    // mean + SD of sitting
    // printf("\nMean of sitting: %f", normal.sitting_mean);
    // printf("\nSD of sitting: %f", normal.sitting_standard_deviation);

    // Gaussian Probability of age and sitting
    // for (size_t i = 81; i < 100; i++)
    // {
    //     printf("\ntest guassian normal prob %d: %1.30lf",i, Gaussian_probability(semen_array[i], normal));
    //     printf("\ntest guassian altered prob %d: %1.30lf",i, Gaussian_probability(semen_array[i], altered));
    // }

    // Training Set Posterior Probability
    // for (size_t i = 0; i < training_set; i++)
    // {
    //     printf("\n%d -> Normal Posterior Probability: %1.30lf", i+1, Posterior_Probability(i, normal));
    //     printf("\n%d -> Altered Posterior Probability: %1.30lf", i+1, Posterior_Probability(i, altered));
    // }

    // Training Set NB Prediction
    // for (size_t i = 0; i < training_set; i++)
    // {
    //     printf("\n%d -> Prediction: %d", i+1, NB_Prediction(Posterior_Probability(i, normal), Posterior_Probability(i, altered)));
    // }
}

// calculates prior probability
void Prior_Probability()
{
    //probability for being altered or normal
    float altered_probability = 0;
    float normal_probability = 0;

    for (int i = 0; i < training_set; i++)
    {
        if (semen_array[i][s_col - 1] == 1.0f) //assume last rows = results
            altered_probability++;
        else
            normal_probability++;
    }
    altered_probability /= s_row;
    normal_probability /= s_row;

    // Store value in struct Probability variable
    altered.prior_probability = altered_probability;
    normal.prior_probability = normal_probability;
}

void Prob_Season()
{
    int alpha = SEASON_ALPHA;
    float aprobability[4] = {0};
    float nprobability[4] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][0] == -1.0f)
                nprobability[0]++;

            else if (semen_array[i][0] == -0.33f)
                nprobability[1]++;

            else if (semen_array[i][0] == 0.33f)
                nprobability[2]++;

            else if (semen_array[i][0] == 1.0f)
                nprobability[3]++;
            else
                printf("\nError in line %d for Seasons value = \"%.2f\" skipping entry, only input (-1, -0.33, 0.33, 1)", (i + 1), semen_array[i][0]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][0] == -1.0f)
                aprobability[0]++;

            else if (semen_array[i][0] == -0.33f)
                aprobability[1]++;

            else if (semen_array[i][0] == 0.33f)
                aprobability[2]++;

            else if (semen_array[i][0] == 1.0f)
                aprobability[3]++;
            else
                printf("\nError in line %d for Seasons value = \"%.2f\" skipping entry, only input (-1, -0.33, 0.33, 1)", (i + 1), semen_array[i][0]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.winter_probability = aprobability[0];
    altered.spring_probability = aprobability[1];
    altered.summer_probability = aprobability[2];
    altered.fall_probability = aprobability[3];
    normal.winter_probability = nprobability[0];
    normal.spring_probability = nprobability[1];
    normal.summer_probability = nprobability[2];
    normal.fall_probability = nprobability[3];
}

void Prob_Childish_Disease()
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][2] == 1)
                nprobability[0]++;

            else if (semen_array[i][2] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Childish Disease value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][2]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][2] == 1)
                aprobability[0]++;

            else if (semen_array[i][2] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Childish Disease value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][2]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.no_disease_probability = aprobability[0];
    altered.disease_probability = aprobability[1];
    normal.no_disease_probability = nprobability[0];
    normal.disease_probability = nprobability[1];
}

void Prob_Accident()
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][3] == 1)
                nprobability[0]++;

            else if (semen_array[i][3] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Accident/Trauma value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][3]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][3] == 1)
                aprobability[0]++;

            else if (semen_array[i][3] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Accident/Trauma value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][3]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.no_trauma_probability = aprobability[0];
    altered.trauma_probability = aprobability[1];
    normal.no_trauma_probability = nprobability[0];
    normal.trauma_probability = nprobability[1];
}

void Prob_Surgical_Intervention()
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][4] == 1)
                nprobability[0]++;

            else if (semen_array[i][4] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Surgical Intervention value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][4]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][4] == 1)
                aprobability[0]++;

            else if (semen_array[i][4] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Surgical Intervention value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][4]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.no_surgery_probability = aprobability[0];
    altered.surgery_probability = aprobability[1];
    normal.no_surgery_probability = nprobability[0];
    normal.surgery_probability = nprobability[1];
}

void Prob_Fever()
{
    int alpha = F_S_ALPHA;
    float aprobability[3] = {0};
    float nprobability[3] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][5] == -1)
                nprobability[0]++;

            else if (semen_array[i][5] == 0)
                nprobability[1]++;

            else if (semen_array[i][5] == 1)
                nprobability[2]++;

            else
                printf("\nError in line %d for High fevers in last year value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][5]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][5] == -1)
                aprobability[0]++;

            else if (semen_array[i][5] == 0)
                aprobability[1]++;

            else if (semen_array[i][5] == 1)
                aprobability[2]++;

            else
                printf("\nError in line %d for High fevers in last year value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][5]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.fever_less3m_probability = aprobability[0];
    altered.fever_more3m_probability = aprobability[1];
    altered.no_fever_probability = aprobability[2];
    normal.fever_less3m_probability = nprobability[0];
    normal.fever_more3m_probability = nprobability[1];
    normal.no_fever_probability = nprobability[2];
}
void Prob_Alcohol_Consumption()
{
    int alpha = ALCOHOL_ALPHA;
    float aprobability[5] = {0};
    float nprobability[5] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][6] == 0.2f)
                nprobability[0]++;

            else if (semen_array[i][6] == 0.4f)
                nprobability[1]++;

            else if (semen_array[i][6] == 0.6f)
                nprobability[2]++;

            else if (semen_array[i][6] == 0.8f)
                nprobability[3]++;

            else if (semen_array[i][6] == 1.f)
                nprobability[4]++;

            else
                printf("\nError in line %d for Frequency of alcohol consumption value = \"%.2f\" skipping entry, only input (0.2, 0.4, 0.6, 0.8, 1)", (i + 1), semen_array[i][6]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][6] == 0.2f)
                aprobability[0]++;

            else if (semen_array[i][6] == 0.4f)
                aprobability[1]++;

            else if (semen_array[i][6] == 0.6f)
                aprobability[2]++;

            else if (semen_array[i][6] == 0.8f)
                aprobability[3]++;

            else if (semen_array[i][6] == 1.f)
                aprobability[4]++;

            else
                printf("\nError in line %d for Frequency of alcohol consumption value = \"%.2f\" skipping entry, only input (0.2, 0.4, 0.6, 0.8, 1)", (i + 1), semen_array[i][6]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.alcohol_several_day_probability = aprobability[0];
    altered.alcohol_everyday_probability = aprobability[1];
    altered.alcohol_several_week_probability = aprobability[2];
    altered.alcohol_once_week_probability = aprobability[3];
    altered.alcohol_hardly_probability = aprobability[4];
    normal.alcohol_several_day_probability = nprobability[0];
    normal.alcohol_everyday_probability = nprobability[1];
    normal.alcohol_several_week_probability = nprobability[2];
    normal.alcohol_once_week_probability = nprobability[3];
    normal.alcohol_hardly_probability = nprobability[4];
}

void Prob_Smoking()
{
    int alpha = F_S_ALPHA;
    float aprobability[3] = {0};
    float nprobability[3] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][7] == -1)
                nprobability[0]++;

            else if (semen_array[i][7] == 0)
                nprobability[1]++;

            else if (semen_array[i][7] == 1)
                nprobability[2]++;

            else
                printf("\nError in line %d for Smoking Habit value = \"%.2f\" skipping entry, only input (-1, 0, 1)", (i + 1), semen_array[i][7]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][7] == -1)
                aprobability[0]++;

            else if (semen_array[i][7] == 0)
                aprobability[1]++;

            else if (semen_array[i][7] == 1)
                aprobability[2]++;

            else
                printf("\nError in line %d for Smoking Habit value = \"%.2f\" skipping entry, only input (-1, 0, 1)", (i + 1), semen_array[i][7]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.smoke_never_probability = aprobability[0];
    altered.smoke_occasional_probability = aprobability[1];
    altered.smoke_daily_probability = aprobability[2];
    normal.smoke_never_probability = nprobability[0];
    normal.smoke_occasional_probability = nprobability[1];
    normal.smoke_daily_probability = nprobability[2];
}

void Prob_Age()
{
    float mean[2] = {0, 0}, sd[2] = {0, 0};
    Mean(1, mean);
    normal.age_mean = mean[0];
    altered.age_mean = mean[1];
    Standard_Deviation(1, mean, sd);
    normal.age_standard_deviation = sd[0];
    altered.age_standard_deviation = sd[1];
}

void Prob_Sitting()
{
    float mean[2] = {0, 0}, sd[2] = {0, 0};
    Mean(8, mean);
    normal.sitting_mean = mean[0];
    altered.sitting_mean = mean[1];
    Standard_Deviation(8, mean, sd);
    normal.sitting_standard_deviation = sd[0];
    altered.sitting_standard_deviation = sd[1];
}

void Mean(int column, float mean[])
{
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            mean[0] += semen_array[i][column];
            normalcount++;
            break;

        case 1: // Altered
            mean[1] += semen_array[i][column];
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //returns average of the column
    mean[0] /= normalcount;
    mean[1] /= (training_set - normalcount);
}
//assume mean is already calculated
void Standard_Deviation(int column, float mean[], float sd[])
{
    int normalcount = 0;
    //used for temporary storage of data-mean to not alter data in semen_array
    float temp = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            temp = semen_array[i][column] - mean[0];
            sd[0] += pow(temp, 2);
            normalcount++;
            break;

        case 1: // Altered
            temp = semen_array[i][column] - mean[1];
            sd[1] += pow(temp, 2);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //returns average of the column
    sd[0] /= (normalcount - 1);
    sd[1] /= (training_set - normalcount - 1);
}

//returns average of the column
float Gaussian_Probability(float data[], struct probability probability)
{
    float age, sitting;
    age = (1 / sqrt(2 * M_PI)) * exp(-0.5 * pow((data[1] - probability.age_mean) / probability.age_standard_deviation, 2));
    sitting = (1 / sqrt(2 * M_PI)) * exp(-0.5 * pow((data[8] - probability.sitting_mean) / probability.sitting_standard_deviation, 2));
    return age * sitting;
}

//returns posterior probability for altered and normal
double Posterior_Probability(int i, struct probability probability)
{
    double pp;
    // Age and Sitting hours probability
    double gp = Gaussian_Probability(semen_array[i], probability);
    // Seasons probability
    pp = gp * probability.winter_probability * probability.spring_probability * probability.summer_probability * probability.fall_probability;
    // Childish Disease probability
    pp *= probability.disease_probability * probability.no_disease_probability;
    // Accident / Serious Trauma probability
    pp *= probability.trauma_probability * probability.no_trauma_probability;
    // Surgical Intervention probability
    pp *= probability.surgery_probability * probability.no_surgery_probability;
    // Fever probability
    pp *= probability.fever_less3m_probability * probability.fever_more3m_probability * probability.no_fever_probability;
    // Alcohol Consumption probability
    pp *= probability.alcohol_several_day_probability * probability.alcohol_everyday_probability * probability.alcohol_several_week_probability * probability.alcohol_once_week_probability * probability.alcohol_hardly_probability;
    // Smoking Habits probability
    pp *= probability.smoke_never_probability * probability.smoke_occasional_probability * probability.smoke_daily_probability;
    // Prior probability
    pp *= probability.prior_probability;
    return pp;
}

//returns nb prediction based on Posterior Probability
int NB_Prediction(double pp_normal, double pp_altered)
{
    int res = 1; // 1 = altered
    if (pp_normal >= pp_altered)
    {
        res = 0; // 0 = normal
    }
    return res;
}

//stores probability of error in an array after making final predictions
double **Make_Predict(int start_count, int end_count, int size)
{
    int count = 0;
    double error_sum = 0;
    double error_probability;
    double **prob_error_arr = malloc(size * sizeof(double *));

    for (size_t i = start_count; i < end_count; i++)
    {
        double pp_normal = Posterior_Probability(i, normal);
        double pp_altered = Posterior_Probability(i, altered);
        int predicted_res = NB_Prediction(pp_normal, pp_altered);
        int real = semen_array[i][s_col - 1];
        // check if predicted outcome = real outcome
        if (predicted_res != real)
        {
            error_sum ++;
        }
        // calculates probability of error
        error_probability = 1.0 / end_count * error_sum;
        // adds probability of error to array
        prob_error_arr[count] = malloc(1 * sizeof(double *));
        prob_error_arr[count][0] = error_probability;
        count ++;
    }
    return prob_error_arr;
}

//plots the error probability graph
void Plot_Graph(int terminal, char *name, int size, double **prob_error_arr)
{
    const char *ylabel = "Error Probability";
    const char *xlabel = "Data No.";
    // open persistent gnuplot window
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    // basic settings
    fprintf(gnuplot_pipe, "set terminal qt %d\n", terminal);
    fprintf(gnuplot_pipe, "set title '%s'\n", name);
    fprintf(gnuplot_pipe, "set ylabel '%s' textcolor rgb '#0060ad'\n", ylabel);
    fprintf(gnuplot_pipe, "set xlabel '%s' textcolor rgb '#FF7000'\n", xlabel);
    fprintf(gnuplot_pipe, "set grid\n");
    fprintf(gnuplot_pipe, "set style line 1 linecolor rgb '#0060ad' ");
    fprintf(gnuplot_pipe, "linetype 1 linewidth 1 pointtype 7 pointsize 1\n");
    // fill it with data
    fprintf(gnuplot_pipe, "plot '-' with linespoints linestyle 1\n");
    for (size_t i = 0; i < size; ++i)
    {
        fprintf(gnuplot_pipe, "%zu %f\n", i, prob_error_arr[i][0]);
    }
    fprintf(gnuplot_pipe, "e\n");
    // refresh can probably be omitted
    fprintf(gnuplot_pipe, "refresh\n");
}
