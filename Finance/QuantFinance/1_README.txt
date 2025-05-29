Algo trading -- Using complex algroithms which look at market data, liquidity, time, market sentiments to automatically workout best times to buy and sell stocks i.e. no human intervention. Example: VWAP is an algo strategy.

discretionary trading -- Doing everything manually.

Can start here too, there are very important and informative links.
https://www.quantstart.com/articles/Quantitative-Finance-Reading-List/
https://www.quantstart.com/
https://www.quantstart.com/articles/

The most important advantage of algo trading is that you cab backtest your strategy on historical market data, which is (hopefully) a representative of future market data. Plus there is no need for any human to constantly monitor the market for price action or new input.

Important things in a trading system design are:
1. signal generation
2. risk management
3. performance measurement (how good is your systematic trading generating profits)
4. position sizing/leverage
5. portfolio optimisation and execution (i.e. speed of executing trades, i.e. exchange connectivity layer).

As you may have a stable of algo strategies, it is necessary to automatically adjust leverage and risk factors dynamically, directly responding to market dynamics in real-time.

For comparing systematic strategies, you look at statistical information on both historical and current performance. By looking at historical and current performance it is possible to determine equity growth, risk (in various forms). This allows an "apple to apples" comparison between various strategies such that capital can be allocated optimally.

Scientific Method vs data mining (or black box) approach
========================================================
The best way to design strategies is using the scientific method. In this method, you first formulate a question like: Is there a relationship between the SPDR Gold Shares ETF (GLD) and the Market Vector Gold Miners ETF(GDX)? So you have a Hypothesis and a Null Hypothesis for that question. Example:
Hypothesis or Alternate Hypothesis: The spread between the GLD and GDX have mean-reverting behavior. I will to what mean-reverting means in some time.
Null Hypothesis: The spread between the GLD and GDX is just a random-walk.
Then off course you will do some analysis assuming the null hypothesis and come out with a P-value. Example, you may look at time series data and show that the spread between GLD-GDX is indeed constant. There are many methods for that analysis. The result of the testing procedure will provide a statistical answer whether the null hypothesis can be rejected at a certain level of confidence (P value). Sometimes, even when null hypothesis can't be rejected, using a larger data set or adding more input (like a third ETF affecting the price) can also be tested. This is the whole process of analysis in scientific method. Often it leads to the rejection of the null hypothesis.

The most important benefit of scientific method, is that in future if your strategy breaks down after a period of good profitability, it is possible to revisit the initial hypothesis and re-evaluate it, potentially leading to a new hypothesis that leads to a regained profitability for a strategy.

In contrast, the data mining or black box approach is where a large quantity of parameters or "indicators" are applied to a time series data. If such a "strategy" is initially profitable and then performance deteriorates it is difficult to determine why. It often leads to arbitrary application of new information, indicators or parameters that may temporarily lead to profitability but subsequently lead to further performance degradation. In this instance the strategy is usually discarded and the process of "research" continues again.
