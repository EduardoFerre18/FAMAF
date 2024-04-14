import requests
from datetime import date


def get_url(year):
    return f"https://nolaborables.com.ar/api/v2/feriados/{year}"


months = ['Enero', 'Febrero', 'Marzo', 'Abril', 'Mayo', 'Junio',
          'Julio', 'Agosto', 'Septiembre', 'Octubre', 'Noviembre', 'Diciembre']
days = ['Lunes', 'Martes', 'Miércoles',
        'Jueves', 'Viernes', 'Sábado', 'Domingo']


def day_of_week(day, month, year):
    return days[date(year, month, day).weekday()]


class NextHoliday:
    def __init__(self):
        self.loading = True
        self.year = date.today().year
        self.holiday = None

    def set_next(self, holidays):
        now = date.today()
        today = {
            'day': now.day,
            'month': now.month
        }

        holiday = next(
            (h for h in holidays if h['mes'] == today['month']
             and h['dia'] > today['day'] or h['mes'] > today['month']),
            holidays[0]
        )

        self.loading = False
        self.holiday = holiday

    # Busca el proximo feriado que sea de tipo type.
    # Si lo encuentra lo asigna a self.holiday,
    # caso contrario self.holiday = None
    def set_next_type(self, holidays, type):
        now = date.today()
        today = {
            'day': now.day,
            'month': now.month
        }

        holiday = next(
            (h for h in holidays if (h['mes'] == today['month'] and h['dia'] >
             today['day'] or h['mes'] > today['month']) and h['tipo'] == type),
            None
        )

        self.loading = False
        self.holiday = holiday

    def fetch_holidays(self):
        response = requests.get(get_url(self.year))
        data = response.json()
        self.set_next(data)
        # Linea para testear la funcion set_next_type
        # self.set_next_type(data, 'inamovible')

    def render(self):
        if self.loading:
            print("Buscando...")
        elif self.holiday == None:
            print("No existe el feriado buscado")
        else:
            print("Próximo feriado")
            print(self.holiday['motivo'])
            print("Fecha:")
            print(day_of_week(self.holiday['dia'],
                  self.holiday['mes'], self.year))
            print(self.holiday['dia'])
            print(months[self.holiday['mes'] - 1])
            print("Tipo:")
            print(self.holiday['tipo'])


next_holiday = NextHoliday()
next_holiday.fetch_holidays()
next_holiday.render()
