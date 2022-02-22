# Import libraries
import requests
import urllib.request
import time
from bs4 import BeautifulSoup
import csv
import sys
import json
from selenium import webdriver
import selenium
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains

def scrap_schedule(year,month,day):

    day = day-2

    if day == -1 :
        day = 30
        month = month-1

    if month == 0:
        month = 12
        year = year-1
    
    #Loop over IDs
    for x in range(0,3):

        day=day+1

        if day==32:
            day=1
            month=month+1

        if month==13:
            month=1
            year=year+1

    
        # Set the URL you want to webscrape from
        Sday = str(day)
        Smonth = str(month)
        if day < 10:
            Sday = '0'+str(day)
        if month < 10:
            Smonth = '0'+str(month)

        if str(year)+Smonth+Sday=='20220220':
            continue
    
        if str(year)+Smonth+Sday=='20220229':
            continue

        url = 'https://www.espn.com/nba/scoreboard/_/date/'+str(year)+Smonth+Sday
        print(url)

        d = webdriver.Chrome("/local/home/ar245054/AndroidAssests/HotPicks/OLD_STUFF/Scrapper/chromedriver")

        d.get(url)

        # Connect to the URL
        pageSourcemain = d.page_source

        # Parse HTML and save to BeautifulSoup object
        soup = BeautifulSoup(pageSourcemain, "html.parser")
        
        # Connect to the URL
        #response = requests.get(url)

        # Parse HTML and save to BeautifulSoup object
        #soup = BeautifulSoup(response.text, "html.parser")

        urlname = soup.find_all('meta', attrs={'property':'og:url'})
        #print('url',urlname[0]['content'])
        if urlname[0]['content']!=url:
            continue
    
        # create and write headers to a list 
        rows = []
        rows.append(['TeamH','TeamA','Id','Time',''])
        TeamH = []
        TeamA = []
        Time = []
        Id = []
        #find results within table
        #table = soup.find('body', attrs={'class': 'col column-one gamepackage-away-wrap'})
        body = soup.find('body')
        #hometeam = body.find_all('li', attrs={'class': 'ScoreboardScoreCell__Item flex items-center relative pb2 ScoreboardScoreCell__Item--home'})
        teams = body.find_all('a', attrs={'class': 'AnchorLink truncate'})
        #print('Number of Teams', len(teams))
        gameid = body.find_all('section', attrs={'class': 'Scoreboard bg-clr-white flex flex-auto justify-between'})
        #print('Number of Game Id', len(gameid))
        time = body.find_all('div', attrs={'class': 'ScoreCell__Time ScoreboardScoreCell__Time h9 clr-gray-03'})
        #print('Number of Time', len(time))

        if len(gameid) == 0:
            continue
    
        count = 0
    
        # loop over hometeam
        for team in teams:

            data = team.find_all('div', attrs={'class': 'ScoreCell__TeamName ScoreCell__TeamName--shortDisplayName truncate db'})

            #print('Number of results', len(data))
            # write data to variables
            if count==1:
                TeamH.append(data[0].getText())
                count=0
            else:
                TeamA.append(data[0].getText())
                count=1
            #print(data[0].getText())

        for z in range(0,len(gameid)):

            Id.append(gameid[z]['id'])
            #print(gameid[z]['id'])

        for k in range(0,len(time)):
            Time.append(time[k].getText())
            
        for y in range(0,len(gameid)):
            if len(time)==0:
                rows.append([TeamH[y],TeamA[y],Id[y],'0',''])
            else:
                rows.append([TeamH[y],TeamA[y],Id[y],Time[y],''])
        
        #print(rows)
        #print(len(rows))
        # Create csv and write rows to output file
        fileN = 'NBA_Data/2021_2022/schedule/Schedule_'+str(year)+Smonth+Sday+'.csv'
        with open(fileN,'w', newline='') as f_output:
            csv_output = csv.writer(f_output)
            csv_output.writerows(rows)

if __name__ == "__main__":
    year = int(sys.argv[1])
    day = int(sys.argv[3])
    month = int(sys.argv[2])
    scrap_schedule(year,month,day)


