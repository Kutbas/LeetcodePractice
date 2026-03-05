import time
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from webdriver_manager.chrome import ChromeDriverManager

username="16685335453"
password="myx20020109"

# 编写自动化脚本

# 1.打开浏览器
ChromeIns = ChromeDriverManager().install()
# 2.创建浏览器驱动对象
driver = webdriver.Chrome(service=Service(ChromeIns))
time.sleep(2)
# 3.输入京东网址
driver.get("https://passport.jd.com/")
time.sleep(2)
# 获取登录按钮
login_button = driver.find_element(By.CLASS_NAME, "no_login_btn")
login_button.click()  # 执行点击
# 输入用户名
driver.find_element(By.CSS_SELECTOR, "#loginname").send_keys(username)
time.sleep(2)
# 输入密码
driver.find_element(By.CSS_SELECTOR, "#nloginpwd").send_keys(password)
time.sleep(2)
# 登录
login_submit = driver.find_element(By.CSS_SELECTOR, "#loginsubmit")
login_submit.click()
time.sleep(2)

# 4.点击“百度一下”按钮
# driver.find_element(By.CSS_SELECTOR, "#su").click()
# time.sleep(2)
# 5.关闭浏览器

driver.quit()

#hotsearch-content-wrapper > li:nth-child(1) > a > span.title-content-title
#J_user > div > div.login_info_container > a