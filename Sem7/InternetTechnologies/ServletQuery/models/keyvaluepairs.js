'use strict';
module.exports = (sequelize, DataTypes) => {
  const KeyValuePairs = sequelize.define('KeyValuePairs', {
    key: DataTypes.STRING,
    value: DataTypes.STRING
  }, {});
  KeyValuePairs.associate = function(models) {
    // associations can be defined here
  };
  return KeyValuePairs;
};