using System;
using UnityEngine;

namespace Code.Player
{
    public class PlayerShoot : MonoBehaviour
    {
        [SerializeField] private Transform _spawnPoint = null;
        [SerializeField] private Rigidbody _bulletPrefab = null;
        [SerializeField] private float _shootForce = 10.0f;

        private Rigidbody[] _bullets = new Rigidbody[50];

        private void Start()
        {
            Transform parent = new GameObject("Bullets").transform;
            for (int i = 0; i < _bullets.Length; i++)
            {
                _bullets[i] = Instantiate(_bulletPrefab, parent);
                _bullets[i].gameObject.SetActive(false);
            }
        }

        private void Update()
        {
            if (Input.GetButtonDown("Fire1"))
            {
                // // invisible bullet
                // RaycastHit hit;
                // if (Physics.Raycast(_spawnPoint.position, _spawnPoint.forward, out hit))
                // {
                //     Debug.LogFormat("Hit: {0}", hit.transform.name);
                // }
                
                // visible bullet
                // Rigidbody bullet = Instantiate(_bulletPrefab, _spawnPoint.position, _spawnPoint.rotation);
                // bullet.AddForce(bullet.transform.forward * _shootForce, ForceMode.Impulse);
                // Destroy(bullet.gameObject, 3.0f);
                
                // object pool
                for (int i = 0; i < _bullets.Length; i++)
                {
                    if (_bullets[i].gameObject.activeSelf) continue;
                    
                    _bullets[i].gameObject.SetActive(true);
                    _bullets[i].transform.SetPositionAndRotation(_spawnPoint.position, _spawnPoint.rotation);
                    _bullets[i].AddForce(_bullets[i].transform.forward * _shootForce, ForceMode.Impulse);
                    
                    break;
                }
            }
        }
    }
}