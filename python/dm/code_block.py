
# load data
df_train = pd.read_csv(
    '../input/train.csv', usecols=[1, 2, 3, 4, 5],
    dtype={'onpromotion': bool},
    converters={'unit_sales': lambda u: np.log1p(
        float(u)) if float(u) > 0 else 0},
    parse_dates=["date"],
    skiprows=range(1, 66458909)  # 2016-01-01
)

# set index
items = pd.read_csv(
    "../input/items.csv",
).set_index("item_nbr")

# gc asap
import gc
del df_train

# condition choose
df_2017 = df_train.loc[df_train.date>=pd.datetime(2017,1,1)]

# date range
pd.date_range(start='1/1/2018', periods=8)
DatetimeIndex(['2018-01-01', '2018-01-02', '2018-01-03', '2018-01-04',
               '2018-01-05', '2018-01-06', '2018-01-07', '2018-01-08'],
              dtype='datetime64[ns]', freq='D')

# get index level column
promo_2017_train.columns = promo_2017_train.columns.get_level_values(1)
# high usage don't know
promo_2017_test = df_test[["onpromotion"]].unstack(level=-1).fillna(False)
