<template>
  <div class="mapTraking">
    <div>
      <br />
      <br />
      <h2 class="h2-gateway-tricker">Gateway Tracking</h2>
      <!-- {{markers}} -->

      <!-- <label>
        <gmap-autocomplete
          @place_changed="setPlace">
        </gmap-autocomplete>
        <button @click="addMarker">Add</button>
      </label>-->
      <br />
    </div>
    <br />

    <gmap-map :center="center" :zoom="12" style="width:100%;  height: 600px;">
      <gmap-marker
        :key="index"
        v-for="(m, index) in markers"
        :position="m.position"
        icon="https://img.icons8.com/ultraviolet/40/000000/marker.png"
        @click="show=true,datalog(m)"
      >
        <a href="https://www.youtube.com"></a>
      </gmap-marker>
    </gmap-map>
    <b-modal v-model="show" id="modal-scrollable" centered scrollable title="Node">
      <b-row class="row_show_node" v-for="(item, index) in idnode_index" :key="index">
        <b-col cols="6">
          {{gatewayname}} :
          <br />
          {{place_gateway}} :
          <br />
          {{idnode}} :
          <br />
          {{sensor}} :
          <br />
          {{place_node}} :
        </b-col>
        <b-col cols="6">
          {{gatewayname_index[index]}}
          <br />
          {{place_gateway_index[index]}}
          <br />
          {{idnode_index[index]}}
          <br />
          {{sensor_index[index]}}
          <br />
          {{place_node_index[index]}}
        </b-col>

        <b-col cols="12" class="col-button">
          <b-progress class="mt-2" max="100" show-value animated>
            <b-progress-bar
              :value="sensor_index[index]"
              variant="danger"
              v-if="sensor_index[index] >= 80"
            ></b-progress-bar>

            <b-progress-bar
              :value="sensor_index[index]"
              variant="warning"
              v-else-if="sensor_index[index] >= 50"
            ></b-progress-bar>

            <b-progress-bar :value="sensor_index[index]" variant="success" v-else></b-progress-bar>
          </b-progress>
          <br />
          <b-button
            class="historbutton"
            block
            variant="info"
            @click="lookhistory(),saveidnode(item)"
          >
            <h6>History node {{idnode_index[index]}}</h6>
          </b-button>
        </b-col>
      </b-row>
      <template v-slot:modal-footer="{ ok, cancel, hide }">
        <!-- Emulate built in modal footer ok and cancel button actions -->
        <b-button size="md" variant="info" @click="ok()">ตกลง</b-button>
      </template>
    </b-modal>
    <div></div>
  </div>
</template>

<script>
import axios from "axios";
//icon = "https://img.icons8.com/ultraviolet/40/000000/marker.png"

export default {
  name: "GoogleMap",
  data() {
    return {
      //13.821582, 100.519540
      show: false,
      center: { lat: 13.821582, lng: 100.51954 },
      markers: [],
      places: [],
      data_test: null,
      currentPlace: null,
      //pin: URL('./../img/gps.png'),

      idgateway: "Id of gateway",
      gatewayname: "Gateway name",
      place_gateway: "Place of gateway",
      idnode: "Id of node",
      sensor: "Realtime sensor",
      status_node: "Status in garbage",
      place_node: "Place of node",

      idgateway_index: ["loading"],
      gatewayname_index: ["loading"],
      place_gateway_index: ["loading"],
      idnode_index: ["loading"],
      sensor_index: ["loading"],
      status_node_index: ["loading"],
      place_node_index: ["loading"],

      ColorStatus: [],
      max: 100
    };
  },
  mounted() {
    this.geolocate();
  },
  methods: {
    saveidnode(item) {
      this.$store.state.node_id = "";
      this.$store.state.node_id = item;
    },
    lookhistory() {
      this.$router.push("/history");
    },
    datalog(m) {
      this.data_test = m.message;
      axios
        .post("`${API}`/gateway", {
          id: this.data_test
        })
        .then(response => {
          if (response.data.success == "success") {
            this.idgateway_index = [];
            this.gatewayname_index = [];
            this.place_gateway_index = [];
            this.idnode_index = [];
            this.sensor_index = [];
            this.status_node_index = [];
            this.place_node_index = [];
            this.ColorStatus = [];

            for (let i = 0; i < response.data.message.length; i++) {
              this.idgateway_index.push(response.data.message[i].id);
              this.gatewayname_index.push(
                response.data.message[i].gateway_name
              );
              this.place_gateway_index.push(response.data.message[i].place);
              this.idnode_index.push(response.data.message[i].idnode);
              this.sensor_index.push(response.data.message[i].sensor);
              this.status_node_index.push(response.data.message[i].status_name);
              this.place_node_index.push(response.data.message[i].place_node);
              // if(response.data.message[i].sensor >= 80){
              //   this.ColorStatus.push("success")
              // }else if(response.data.message[i].sensor >= 40){
              //   this.ColorStatus.push("warning")
              // }else{
              //   this.ColorStatus.push("danger")
              // }
            }
          }
        });

      //let colorStatus;
    },
    pullThelatlng() {
      axios.post("`${API}`/trackgateway", {}).then(response => {
        if (response.data.success == "success") {
          for (let index = 0; index < response.data.message.length; index++) {
            this.markers.push({
              position: {
                lat: response.data.message[index].lad,
                lng: response.data.message[index].lng
              },

              message: response.data.message[index].id
            });
          }
        } else {
          alert(response.data.message);
        }
      });
    },
    // receives a place object via the autocomplete component
    //รับที่อยู่ใส่ใน currentPlace
    setPlace(place) {
      this.currentPlace = place;
    },
    // addMarker() {
    //   if (this.currentPlace) {
    //     const marker = {
    //       lat: this.currentPlace.geometry.location.lat(),
    //       lng: this.currentPlace.geometry.location.lng()
    //     };
    //     this.markers.push({ position: marker });
    //     this.places.push(this.currentPlace);
    //     this.center = marker;
    //     this.currentPlace = null;
    //   }
    // },
    geolocate: function() {
      navigator.geolocation.getCurrentPosition(position => {
        this.center = {
          lat: position.coords.latitude,
          lng: position.coords.longitude
        };
        /* eslint-disable no-console */
        console.log(position);
        /* eslint-enable no-console */
      });
    }
  },
  beforeMount() {
    this.pullThelatlng();
  }
};
</script>
<style lang="css" >
.historbutton {
  margin-bottom: -17%;
  margin-top: 5%;
  text-align: center;
  padding-top: 2%;
}

h6 {
  padding: 0%;
  margin: 0%;
}

.mapTraking {
  margin: 0%;
  padding-top: 7%;
}

.h2-gateway-tricker {
  color: #070606;
  padding-bottom: 40px;
  padding-top: -10px;
  margin-top: -5%;
}

.modal-dialog-scrollable .modal-body {
  padding-bottom: 0%;
}

/* .row_show_node{
  border-bottom: solid 1px #0000;
} */

/* .row.history_link{
  width: 100%;
  margin:0%;
  padding: 0%;

} */

div.col-button.col-12 {
  padding: 5%;
}

button.btn.historbutton {
  margin: auto;
}

div.row.row_show_node {
  margin-bottom: 0;
}
</style>

