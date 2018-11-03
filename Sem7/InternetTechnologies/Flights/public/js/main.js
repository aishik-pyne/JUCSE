var app = new Vue({
  el: '#app',
  data() {
    return {
      api: "http://localhost:15000/api/flights/",
      sources: [],
      destinations: [],
      flights: [],
      pages: 0,
      page: 1,
      source: '',
      destination: '',
      sort: 'cost',
      ord: 'asc'
    }
  },
  computed: {
    processedFlights() {
      return this.flights.map(flight => {
        flight.departure = moment(flight.departure, "HHmm").format('hh:mm A')
        return flight
      })
    }
  },
  created() {
    this.getFlights()
    this.getSources()
    this.getDestinations()
  },
  methods: {
    async getFlights() {
      params = {
        p: this.page,
        ord: this.ord,
        sort: this.sort
      }
      if (this.source.length > 0) 
        params.source = this.source
      if (this.destination.length > 0) 
        params.destination = this.destination

      console.log(`Fetching flights`);
      console.log(params);
      const response = await axios.get(this.api, {
        params
      })
      console.log(await response.data);
      this.flights = await response.data.flights
      this.pages = await response.data.pages
    },
    async getSources() {
      const response = await axios.get(this.api + 'sources')
      this.sources = await response.data
    },
    async getDestinations() {
      const response = await axios.get(this.api + 'destinations')
      this.destinations = await response.data
    },
    changeSort(sort) {
      if (this.sort === sort) {
        this.ord = this.ord === 'asc' ? 'dsc' : 'asc'
      } else {
        this.sort = sort
      }
      this.getFlights()
    }
  },
  mounted() {}
})