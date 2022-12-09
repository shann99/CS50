#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }


    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");

    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    //looks for matching name in candidate array and records the preference for the voter
    for (int z = 0; z < candidate_count ; z++){
        if(strcmp(candidates[z].name, name) == 0){
            preferences[voter][rank] = z;
            return true;
        }
    }
    //if no candidate is found, don't update anything and return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int count = 0;
    int index = 0;
    // TODO
    //update the vote counts for all non-eliminated candiates
    //if a candidate has been eliminated, look to the next candidate
    for(int i = 0; i < voter_count; i++) {
        for(int j = 0; j < candidate_count; j++) {
            //setting count to an arbitrary number
            count = preferences[i][j];
            //checks if preferences[i][j] is greater than or less than candidate count, if it is, increase count
            // this way count can match up to preferences[i][j]
            if(preferences[i][j] > count && count <= candidate_count) {
                count += 1;
            }
            //repeat for the opposite
            else if(preferences[i][j] < count && count > 0) {
                    count -= 1;
            }
            //when preferences[i][j] equals count and the candidate is not eliminated, increase that candidate's vote count
            else if(preferences[i][j] == count){
                index = preferences[i][j];
                if(!candidates[index].eliminated) {
                    candidates[index].votes += 1;
                }
                //if the candidate has been eliminated, increase j (to move to the next rank) and do the count comparison again
                //when count matches pref and the candidate has not been eliminated then increase candidate's vote count then break
                else {
                    while(candidates[index].eliminated){
                        j++;
                        count = preferences[i][j];
                        if(preferences[i][j] > count && count <= candidate_count) {
                            count += 1;
                        }
                        else if(preferences[i][j] < count && count > 0) {
                            count -= 1;
                        }
                        else if(preferences[i][j] == count){
                            index = preferences[i][j];
                            if(!candidates[index].eliminated) {
                                candidates[index].votes += 1;
                                break;
                            }
                        }
                    }
                }
            }
        break;
        }
    }
    return;
}



// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // if a candidate has majority of the votes (more than half of the votes), print their name and return true
    // if no one has one, return false
    double vcount = voter_count;
    double majority = (vcount / 2);
    for(int i = 0; i < voter_count; i++) {
        if(!candidates[i].eliminated) {
            if(candidates[i].votes > majority) {
                printf("%s\n", candidates[i].name);
                return true;
            }
        }
    }
    return false;
}


// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    //return the minimun number of votes in the election
    int min = 0;
    for(int i = 0; i < candidate_count; i++){
        if(!candidates[i].eliminated) {
            //sets the initial min to the first number it encounters then checks through each candidate's votes to see if any of their votes are lower than the min
            //if it is, set it  as the new min
            min = candidates[0].votes;
            if(candidates[i].votes < min) {
                min = candidates[i].votes;
            }
        }
    }
    return min;
}



// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //setting some counters
    int counter = 0;
    int not_eliminated = 0;
    for(int z = 0; z < candidate_count; z++){
        if(!candidates[z].eliminated) {
            //count the number of non eliminated candidates
            not_eliminated++;
            if(min == candidates[z].votes) {
                //if the min number of votes of non eliminated counters matches, increase counter
                counter++;
            }
            else {
                return false;
            }
        }
    }
    //if counter and not_eliminated match, its a tie
    if(counter == not_eliminated){
        printf("Tie!\n");
        return true;
    }
    //else return false
    return false;
}


// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    //if candidate has not been eliminated and their votes are the minimum, eliminate them
    for(int i = 0; i < candidate_count; i++){
        if(!candidates[i].eliminated){
           if(candidates[i].votes == min){
                candidates[i].eliminated = true;
           }
        }
    }
    return;
}