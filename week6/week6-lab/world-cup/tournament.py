# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            team_name = row["team"]
            #converting rating from string to int
            rating = int(row["rating"])
            #creating dict of team name, rating to append to teams list
            team = {
                "team": team_name,
                "rating": rating
            }
            teams.append(team)

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    i = 0
    while i < N:
        winning_team = simulate_tournament(teams)
        #checking if the winning team's name has been in count
        #if it's not, add it in
        if winning_team in counts:
            counts[winning_team] += 1
        else:
            counts[winning_team] = 1
        i += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []
    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
            #print(f"if {winners}")
        else:
            winners.append(teams[i + 1])
            #print(f"else {winners}")
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    #empty array to fill in the first list of wins from the first round of simulate_round
    winners = []
    winners = simulate_round(teams)
    #gets the length of the array of winners
    length = len(winners)
    #if length is great then 1: calculate winners and update length until it reaches 1
    while length > 1:
        winners = simulate_round(winners)
        length = len(winners)
    #gets the name of the winning team by accessing the value where of "team"
    for win in winners:
        winning_team = win['team']
    #returns winning team
    return winning_team


if __name__ == "__main__":
    main()
