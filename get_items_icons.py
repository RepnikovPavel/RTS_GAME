import urllib
import time
import shutil
import os
import re
import requests
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium import webdriver

# you need to scroll through the site page manually to load the content
# the number of headers 3 is specified explicitly
# the number of images under each heading can be arbitrary, this is handled by the try catch construct
# the time before downloading is explicitly specified - 3 seconds.

base_path = './icons'

def clear_dir(folder):
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print('Failed to delete %s. Reason: %s' % (file_path, e))


if not os.path.exists(base_path):
    os.mkdir(base_path)
clear_dir(base_path)

service = Service('./chromedriver.exe')
driver = webdriver.Chrome(service=service)
driver.get('https://dota2.fandom.com/wiki/Items')
time.sleep(3)
# title k-th                    /html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/h3[k]
# image i-th under title k-th   /html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/div[k+3]/div[i]/a[1]/img
# object with image             /html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/div[k+3]/div[i]
# name of item                  /html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/div[k+3]/div[i]/a[2]

for index_of_title in range(1, 28):
    title_obj = driver.find_element(by=By.XPATH,
                                    value="/html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/h3[{}]".format(index_of_title))
    child_of_title = driver.find_element(by=By.XPATH,
                                         value="/html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/h3[{}]/span".format(index_of_title))
    id = child_of_title.get_attribute('id')
    title_name = re.sub('\s+', '_', id)
    title_name = re.sub('\'', '', title_name)
    title_name = re.sub('-', '_', title_name)
    title_name = title_name.lower()
    folder_name = base_path +'/'+title_name
    if os.path.exists(folder_name):
        clear_dir(folder_name)
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)
    index_of_image =  1
    while True:
        try:

            print("index of title {}  index of image {}".format(index_of_title, index_of_image))
            img_element = driver.find_element(by=By.XPATH,
                                              value="/html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/div[{}]/div[{}]/a[1]/img".format(index_of_title+3, index_of_image))
            item_name_object = driver.find_element(by=By.XPATH,
                                                 value="/html/body/div[4]/div[3]/div[3]/main/div[3]/div[1]/div/div[{}]/div[{}]/a[2]".format(index_of_title+3, index_of_image))
            item_name = item_name_object.get_attribute('title')
            item_name = re.sub('\s+','_',item_name)
            item_name = re.sub('\'','',item_name)
            item_name = item_name.lower()
            img_url = img_element.get_attribute('src')
            img_request = requests.get(img_url, stream=True)
            outfile = folder_name + '/' + item_name + '.png'
            with open(outfile, 'wb') as ofstream:
                shutil.copyfileobj(img_request.raw, ofstream)
            index_of_image+=1

        except:
            break

driver.close()