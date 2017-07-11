#-*- coding: utf-8 -*-


import requests
from bs4 import BeautifulSoup

base_url = 'http://news.baidu.com/n?m=rddata&v=hot_word'
hot_type = ''
hot_date = ''
hot_news_word = ''

#爬虫获取百度热搜关键词数据
def geturl(hot_type,hot_date):   
    parameters = {'type': hot_type, 'data':hot_date}
    r = requests.get(base_url, params = parameters)
    print r.url
    hot_words_dict = r.json()
    word_list = []
    for hot_word in hot_words_dict.get('data'):
        word_list.append(hot_word.get('query_word'))
    return word_list

def geturl_print(list):
    for i in range(len(list)):
        print "%d:%s" % (i+1,list[i])

#通过关键词抓取新闻
def getnews(list,hot_news_url):
    hot_news_word = list[hot_news_url-1]
    news_url = 'http://news.baidu.com/ns?tn=news'
    news_parameters = {'word': hot_news_word}
    r_news = requests.get(news_url, params = news_parameters)
    #print r_news.url
    return r_news.url

#列出某一关键词代表的新闻的全部发布信息来源
def detail(url):
    print url
    r_detail = requests.get(url)
    soup = BeautifulSoup(r_detail.text,'lxml')
    news_html_result = soup.select('div.result')
    news_html_list = []
    for news_html in news_html_result:
        news = {}
        news[u'标题'] = news_html.a.get_text().strip()
        news[u'链接'] = news_html.a['href']
        source = news_html.find('p', 'c-author').get_text().strip().split(u'\xa0\xa0')

        news[u'来源'] = source[0]
        news[u'日期'] = source[1]

        news_html_list.append(news)
        
    for news in news_html_list:
        print str(news).replace('u\'','\'').decode("unicode-escape")
 

if __name__ == '__main__':
    print "----------选择热搜类目---------------"
    print "类目选择：0：全部；1：国际；2：国内；3：体育；4：娱乐；5：社会；6：财经；8：科技；10：汽车；14：军事；"
    print "时间输入：如'20170709'"
    print "----------请选择类目编号--------------"
    get_type = input('type=')
    get_date = input('date=')
    news_list=geturl(get_type,get_date)
    geturl_print(news_list)
    get_news_num = input('num=')
    news_detail = getnews(news_list,get_news_num)
    detail(news_detail)

