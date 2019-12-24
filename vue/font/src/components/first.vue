<template>
<div id="first">
    <header-navbar></header-navbar>
    <div class="background-first">
    <b-container>
    <div class="component-gmap">
    <GoogleMap/>
    </div>
    </b-container>
    </div>
</div>
    
</template>

<script>
import GoogleMap from "./Googlemap";
export default {
    components: {
    GoogleMap
  }
}
</script>

<style lang="css">

#first{
    margin: 0;
    padding: 0;
    width: 100%;
    height: 1000px;
}

.background-first{
    background-image: url('./../img/645469-POPYUA-363.jpg');
    background-repeat: no-repeat;
    background-position: center center;
    background-attachment: fixed;
    -o-background-size: 100% 100%, auto;
    -moz-background-size: 100% 100%, auto;
    -webkit-background-size: 100% 100%, auto;
    background-size: 100% 100%, auto;
    position: relative;
    width: 100%;
    height: 100%;
}

html{
    margin: 0%;
    padding: 0%;
}



</style>